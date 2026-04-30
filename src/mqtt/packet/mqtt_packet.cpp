#include "mqtt/packet/mqtt_packet.h"

#include <memory>
#include <iostream>


// Private
uint8_t MQTTPacket::decodeRemainingLength(const uint8_t* stream, size_t maxLength, uint32_t& outValue)
{
  uint32_t multiplier = 1;
  outValue = 0;
  uint8_t bytesRead = 0;
  uint8_t encodedByte;

  do
  {
    if (bytesRead >= maxLength) return 0;

    encodedByte = stream[bytesRead++];
    outValue += (encodedByte & 127) * multiplier;

    if (multiplier > 128 * 128 * 128)
    {
      // Error: Packet too large (max 256MB/4 bytes)
      return 0;
    }
    multiplier *= 128;
  } while ((encodedByte & 128) != 0);
  
  return bytesRead;
}


// Public
std::unique_ptr<MQTTPacket> MQTTPacket::parse(const std::vector<uint8_t>& data)
{
  if (data.size() < 2)
  {
    // The packet is too small to be valid
    return nullptr;
  }

  uint32_t remainingLength = 0;
  uint8_t lengthBytesRead = decodeRemainingLength(data.data()+1, data.size()-1, remainingLength);

  if (lengthBytesRead == 0) 
  {
    // The length is malformed
    return nullptr;
  }

  if (data.size() < 1 + lengthBytesRead + remainingLength)
  {
    // Check if the enitre packet was recieved
    return nullptr;
  }

  MQTTFixedHeader fixedHeader{data[0], remainingLength};

  std::unique_ptr<MQTTVarHeader> varHeader = nullptr;
  size_t varHeaderLength = 0;
  size_t offset = 1 + lengthBytesRead;

  auto it = DECODER_MAP.find(fixedHeader.getType());
  if (it != DECODER_MAP.end())
  {
    varHeader = it->second(data, fixedHeader, offset, varHeaderLength);
    if (!varHeader)
    {
      return nullptr;
    }
  }

  size_t payloadStart = 1 + lengthBytesRead + varHeaderLength;
  size_t payloadLength = remainingLength - varHeaderLength;
  std::vector<uint8_t> payloadBytes{data.begin() + payloadStart, data.begin() + payloadStart + payloadLength};

  MQTTBody body{payloadBytes};

  return std::make_unique<MQTTPacket>(fixedHeader, std::move(varHeader), std::move(body));
}


std::vector<uint8_t> MQTTPacket::serialize()
{
  std::vector<uint8_t> packet;
  std::vector<uint8_t> varHeaderBytes = m_varHeader->encode();

  const std::vector<uint8_t>& payload = m_body.getPayload();
  uint32_t remainingLength = varHeaderBytes.size() + payload.size();

  uint8_t typeAndFlags = (static_cast<uint8_t>(m_fixedHeader.getType()) << 4) |
                         (static_cast<uint8_t>(m_fixedHeader.getFlags()) & 0x0F);
  packet.push_back(typeAndFlags);

  uint32_t len = remainingLength;
  do 
  {
    uint8_t encodedByte = len % 128;
    len /= 128;
    if (len > 0)
    {
      encodedByte |= 128;
    }

    packet.push_back(encodedByte);
  } while (len > 0);

  packet.insert(packet.end(), varHeaderBytes.begin(), varHeaderBytes.end());
  packet.insert(packet.end(), payload.begin(), payload.end());

  return packet;
}
