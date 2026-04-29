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
    /// @returns Single byte containing the username, password, will retain, will QOS, will flag and clean session
    uint16_t getFlags() { return m_connectFlags; }

    /// @returns 16-bit timer telling the broker how long to wait before dropping the packet
    uint16_t getKeepAlive() { return m_keepAlive; }

};


#endif//MQTT_CONNECT_VAR_HEADER