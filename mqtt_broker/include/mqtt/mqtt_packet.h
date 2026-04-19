#ifndef MQTT_PACKET_H
#define MQTT_PACKET_H

#include <memory>

#include "mqtt/mqtt_fixed_header.h"
#include "mqtt/mqtt_var_header.h"


class MQTTBody
{

};


class MQTTPacket
{
  private:
    MQTTFixedHeader m_fixedHeader;                /// Metadata from the packet which says what protocol to use
    std::unique_ptr<MQTTVarHeader> m_varHeader;   /// Metadata from the packet how to interperet data

  public:
    /**
     * @brief Constructs an empty packet with only a header
     * @param header an `MQTTHeader` to give information about the packet
     */
    MQTTPacket(MQTTFixedHeader fixedHeader, std::unique_ptr<MQTTVarHeader> varHeader = nullptr)
    : m_fixedHeader(fixedHeader), m_varHeader(std::move(varHeader))
    {}


    /**
     * @brief Decodes the variable-length "Remaining length" field
     * @param stream An array of bytes starting from the 2nd byte of the packet
     * @param outValue Pointer to store the decoded length
     * @returns The number of bytes consumed (1-4) or 0 if invalid
     */
    uint8_t decodeRemainingLength(const uint8_t* stream, uint32_t& outValue)
    {
      uint32_t multiplier = 1;
      outValue = 0;
      uint8_t bytesRead = 0;
      uint8_t encodedByte;

      do
      {
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

};


#endif//MQTT_PACKET_H