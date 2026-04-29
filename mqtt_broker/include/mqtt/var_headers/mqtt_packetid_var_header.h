#ifndef MQTT_PACKETID_VAR_HEADER
#define MQTT_PACKETID_VAR_HEADER

#include <stdint.h>

#include "mqtt/var_headers/mqtt_var_header.h"


class MQTTPacketIdVarHeader : public MQTTVarHeader
{
  private:
    uint16_t m_packetId;  /// The id of the packet

  public:
    /**
     * @brief Creates a variable packet header with only an id
     * @param packetId The id of the packet
     */
    MQTTPacketIdVarHeader(uint16_t packetId)
    : m_packetId(packetId)
    {}

    
    /**
     * @brief Decodes the MQTT variable header from a byte array
     * @param data The byte array of the packet
     * @param fixedHeader The fixed header of this packet
     * @param offset The current offset of bytes
     * @param varHeaderLength The length of bytes the header is in total
     * @returns An unique pointer to the `MQTTVarHeader` of this packet
     */
    std::unique_ptr<MQTTVarHeader> decode(
      const std::vector<uint8_t>& data,
      const MQTTFixedHeader& fixedHeader,
      size_t& offset, 
      size_t& varHeaderLength
    ) override;
    
    /**
     * @brief Encodes the variable header of this packet to a byte array
     * @param varHeaderBytes The array of bytes which is used in making the final result
     * @returns A byte array of the header
     */
    std::vector<uint8_t> encode() override;


    // Getters
    /// @returns The id of the packet
    uint16_t getPacketId() { return m_packetId; }

};


#endif//MQTT_PACKETID_VAR_HEADER