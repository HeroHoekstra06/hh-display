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
    static uint8_t decodeRemainingLength(const uint8_t* stream, size_t maxLength, uint32_t& outValue);

  public:
    /**
     * @brief Constructs an empty packet with only a header
     * @param header an `MQTTHeader` to give information about the packet
     */
    MQTTPacket(MQTTFixedHeader fixedHeader, std::unique_ptr<MQTTVarHeader> varHeader, MQTTBody body)
    : m_fixedHeader(fixedHeader), m_varHeader(std::move(varHeader)), m_body(std::move(body))
    {}


    /**
     * @brief Creates a `MQTTPacket` from an array of bytes
     * @param data A byte array reprisented by `uint8_t`
     */
    static std::unique_ptr<MQTTPacket> parse(const std::vector<uint8_t>& data);

};


#endif//MQTT_PACKET_H