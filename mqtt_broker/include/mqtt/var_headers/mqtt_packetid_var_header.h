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


    // Getters
    /// @returns The id of the packet
    uint16_t getPacketId() { return m_packetId; }

};


#endif//MQTT_PACKETID_VAR_HEADER