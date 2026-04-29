#include "mqtt/mqtt_packet.h"


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


std::unique_ptr<MQTTPublishVarHeader> MQTTPacket::decodePublishVarHeader(
  const std::vector<uint8_t>& data,
  const MQTTFixedHeader& fixedHeader,
  size_t& offset, 
  size_t& varHeaderLength
)
{
  if (offset + 2 > data.size())
  {
    return nullptr;
  }
  uint16_t topicLen = (data[offset] << 8 | data[offset + 1]);
  offset += 2;

  if (offset + topicLen > data.size())
  {
    return nullptr;
  }
  std::string topic(data.begin() + offset, data.begin() + offset + topicLen);
  offset += topicLen;
  varHeaderLength = 2 + topicLen;

  uint16_t packetId = 0;
  bool hasPacketId = fixedHeader.getQos() > 0;

  if (hasPacketId)
  {
    if (offset + 2 > data.size())
    {
      return nullptr;
    }
    packetId = (data[offset] << 8 | data[offset + 1]);
    varHeaderLength += 2;
    offset += 2;
  }

  return std::make_unique<MQTTPublishVarHeader>(topic, packetId, hasPacketId);
}


std::unique_ptr<MQTTConnectVarHeader> MQTTPacket::decodeConnectVarHeader(
  const std::vector<uint8_t>& data,
  const MQTTFixedHeader& fixedHeader,
  size_t& offset, 
  size_t& varHeaderLength
)
{
  if (offset + data.size())
  { 
    return nullptr;
  }
  uint16_t protoLen = (data[offset] << 8 | data[offset + 1]);
  offset += 2;

  if (offset + protoLen > data.size())
  { 
    return nullptr;
  }
  offset += protoLen;

  if (offset + 4 > data.size()) 
  {
    return nullptr;
  }

  uint8_t level = data[offset++];
  uint8_t flags = data[offset++];
  uint16_t keepAlive = (data[offset] << 8 | data[offset + 1]);

  varHeaderLength = 2 + protoLen + 4;
  return std::make_unique<MQTTConnectVarHeader>(flags, keepAlive, level);
}


std::unique_ptr<MQTTPacketIdVarHeader> MQTTPacket::decodePacketIdVarHeader(
  const std::vector<uint8_t>& data,
  size_t& offset, 
  size_t& varHeaderLength
)
{
  if (offset + 2 > data.size())
  { 
    return nullptr;
  }

  uint16_t packetId = (data[offset] << 8 | data[offset + 1]);
  varHeaderLength = 2;

  return std::make_unique<MQTTPacketIdVarHeader>(packetId);
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

  switch (fixedHeader.getType())
  {
    case Publish:
    {
      varHeader = decodePublishVarHeader(data, fixedHeader, offset, varHeaderLength);
      if (!varHeader)
      {
        // Return if the variable header is a nullptr
        return nullptr;
      }

      break;
    }

    case Connect:
    {
      varHeader = decodeConnectVarHeader(data, fixedHeader, offset, varHeaderLength);
      if (!varHeader)
      {
        // Also return nullptr here because no variable header
        return nullptr;
      }

      break; 
    }

    case Puback:
    case Pubrec:
    case Pubrel:
    case Pubcomp:
    case Subscribe:
    case Suback:
    case Unsubscribe:
    case Unsuback:
    {
      varHeader = decodePacketIdVarHeader(data, offset, varHeaderLength);
      if (!varHeader)
      {
        return nullptr;
      }
      
      break;
    }
    
    default:
      varHeaderLength = 0;
      break;
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
  std::vector<uint8_t> varHeaderBytes;

  switch (m_fixedHeader.getType())
  {
    case Publish:
    {
      auto* pubHeader = dynamic_cast<MQTTPublishVarHeader*>(m_varHeader.get());
      if (pubHeader)
      {
        uint16_t topicLen = pubHeader->getTopicName().length();
        varHeaderBytes.push_back((topicLen >> 8) & 0xFF);
        varHeaderBytes.push_back(topicLen & 0xFF);

        for (char c : pubHeader->getTopicName()) varHeaderBytes.push_back(c);

        if (pubHeader->getHasPacketId())
        {
          uint16_t pid = pubHeader->getPacketId();
          varHeaderBytes.push_back((pid >> 8) & 0xFF);
          varHeaderBytes.push_back(pid & 0xFF);
        }
      }

      break;
    }

    case Connect:
    {
      auto* connHeader = dynamic_cast<MQTTConnectVarHeader*>(m_varHeader.get());
      if (connHeader)
      {
        varHeaderBytes.push_back(0x00);
        varHeaderBytes.push_back(0x04);

        std::string protocolName = "MQTT";
        for (char c : protocolName) varHeaderBytes.push_back(c);

        varHeaderBytes.push_back(4);
        varHeaderBytes.push_back(static_cast<uint8_t>(connHeader->getFlags()));

        uint16_t keepAlive = connHeader->getKeepAlive();
        varHeaderBytes.push_back((keepAlive >> 8) & 0xFF);
        varHeaderBytes.push_back(keepAlive & 0xFF);
      }

      break;
    }

    case Puback:
    case Pubrec:
    case Pubrel:
    case Pubcomp:
    case Subscribe:
    case Suback:
    case Unsubscribe:
    case Unsuback:
    {
      auto* idHeader = dynamic_cast<MQTTPacketIdVarHeader*>(m_varHeader.get());
      if (idHeader)
      {
        uint16_t pid = idHeader->getPacketId();
        varHeaderBytes.push_back((pid >> 8) & 0xFF);
        varHeaderBytes.push_back(pid & 0xFF);
      }

      break;
    }

    default:
      break;
  }

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
