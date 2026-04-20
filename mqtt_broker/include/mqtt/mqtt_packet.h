#ifndef MQTT_PACKET_H
#define MQTT_PACKET_H

#include <memory>

#include "mqtt/mqtt_fixed_header.h"
#include "mqtt/mqtt_var_header.h"
#include "mqtt/mqtt_body.h"


class MQTTPacket
{
  private:
    MQTTFixedHeader m_fixedHeader;                /// Metadata from the packet which says what protocol to use
    std::unique_ptr<MQTTVarHeader> m_varHeader;   /// Metadata from the packet how to interperet data
    MQTTBody m_body;                              /// The actual data from the packet

    /**
     * @brief Decodes the variable-length "Remaining length" field
     * @param stream An array of bytes starting from the 2nd byte of the packet
     * @param outValue Pointer to store the decoded length
     * @returns The number of bytes consumed (1-4) or 0 if invalid
     */
    static uint8_t decodeRemainingLength(const uint8_t* stream, size_t maxLength, uint32_t& outValue)
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

  public:
    /**
     * @brief Constructs an empty packet with only a header
     * @param header an `MQTTHeader` to give information about the packet
     */
    MQTTPacket(MQTTFixedHeader fixedHeader, std::unique_ptr<MQTTVarHeader> varHeader, MQTTBody body)
    : m_fixedHeader(fixedHeader), m_varHeader(std::move(varHeader)), m_body(std::move(body))
    {}


    static std::unique_ptr<MQTTPacket> parse(const std::vector<uint8_t>& data)
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

      // TODO: refactor into multiple smaller functions
      switch (fixedHeader.getType())
      {
        case Publish:
        {
          if (offset + 2 > data.size()) return nullptr;
          uint16_t topicLen = (data[offset] << 8 | data[offset + 1]);
          offset += 2;

          if (offset + topicLen > data.size()) return nullptr;
          std::string topic(data.begin() + offset, data.begin() + offset + topicLen);
          offset += topicLen;
          varHeaderLength = 2 + topicLen;

          uint16_t packetId = 0;
          bool hasPacketId = fixedHeader.getQos() > 0;

          if (hasPacketId)
          {
            if (offset + 2 > data.size()) return nullptr;
            packetId = (data[offset] << 8 | data[offset + 1]);
            varHeaderLength += 2;
          }

          varHeader = std::make_unique<MQTTPublishVarHeader>(topic, packetId, hasPacketId);
          break;
        }

        case Connect:
        {
          if (offset + data.size()) return nullptr;
          uint16_t protoLen = (data[offset] << 8 | data[offset + 1]);
          offset += 2;

          if (offset + protoLen > data.size()) return nullptr;
          offset += protoLen;

          if (offset + 4 > data.size()) return nullptr;
          uint8_t level = data[offset++];
          uint8_t flags = data[offset++];
          uint16_t keepAlive = (data[offset] << 8 | data[offset + 1]);

          varHeaderLength = 2 + protoLen + 4;
          varHeader = std::make_unique<MQTTConnectVarHeader>(flags, keepAlive, level);
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
          if (offset + 2 > data.size()) return nullptr;
          uint16_t packetId = (data[offset] << 8 | data[offset + 1]);
          varHeaderLength = 2;
          varHeader = std::make_unique<MQTTPacketIdVarHeader>(packetId);
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

};


#endif//MQTT_PACKET_H