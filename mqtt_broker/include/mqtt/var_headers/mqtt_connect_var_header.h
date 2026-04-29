#ifndef MQTT_CONNECT_VAR_HEADER
#define MQTT_CONNECT_VAR_HEADER

#include <stdint.h>
#include <string>

#include "mqtt/var_headers/mqtt_var_header.h"


class MQTTConnectVarHeader : public MQTTVarHeader
{
  private:
    std::string m_protocolName; /// The name of the protocol
    uint8_t m_protocolLevel;    /// The version of the protocol
    uint8_t m_connectFlags;     /// Single byte containing the username, password, will retain, will QOS, will flag and clean session
    uint16_t m_keepAlive;       /// A 16-bit timer telling the broker how long to wait before dropping the packet

  public:
    /**
     * @brief Creates a variable header used for connecting with the broker
     * @param flags Single byte containing the username, password, will retain, will QOS, will flag and clean session
     * @param keepAlive A 16-bit timer telling the broker how long to wait before dropping the packet
     * @param level The version of the protocol used
    */
    MQTTConnectVarHeader(uint8_t flags, uint16_t keepAlive, uint8_t level = 4)
    : m_protocolName("MQTT"), m_protocolLevel(level), m_connectFlags(flags), m_keepAlive(keepAlive)
    {}


    // Getters
    /// @returns Single byte containing the username, password, will retain, will QOS, will flag and clean session
    uint16_t getFlags() { return m_connectFlags; }

    /// @returns 16-bit timer telling the broker how long to wait before dropping the packet
    uint16_t getKeepAlive() { return m_keepAlive; }

};


#endif//MQTT_CONNECT_VAR_HEADER