#ifndef MQTT_CONNECT_VAR_HEADER
#define MQTT_CONNECT_VAR_HEADER

#include <stdint.h>
#include <string>

#include "mqtt/packet/var_headers/mqtt_var_header.h"


class MQTTConnectVarHeader : public MQTTVarHeader
{
  private:
    std::string m_protocolName; /// The name of the protocol
    uint8_t m_protocolLevel;    /// The version of the protocol
    uint16_t m_keepAlive;       /// A 16-bit timer telling the broker how long to wait before dropping the packet

    union
    {
      uint8_t raw;
      struct
      {
        uint8_t reserved : 1;       /// A reserved bit. Is always 0
        uint8_t cleanSession: 1;    /// Is this client new, or should it continue a previous session
        uint8_t willFlag : 1;       /// Will the client leave a will upon unplanned disconnection
        uint8_t willQoS : 2;        /// The QoS for the will message
        uint8_t willRetain : 1;     /// If the will is retained by the broker
        uint8_t passwordFlag : 1;   /// If 1, a password must be included in the payload
        uint8_t usernameFlag : 1;   /// If 1, a username must be included in the payload
      };
    } m_connectFlags;
    

  public:
    /**
     * @brief Creates a variable header used for connecting with the broker
     * @param flags Single byte containing the username, password, will retain, will QOS, will flag and clean session
     * @param keepAlive A 16-bit timer telling the broker how long to wait before dropping the packet
     * @param level The version of the protocol used
    */
    MQTTConnectVarHeader(uint8_t flags, uint16_t keepAlive, uint8_t level = 4)
    : m_protocolName("MQTT"), m_protocolLevel(level), m_keepAlive(keepAlive)
    {
      m_connectFlags.raw = flags;
    }


    /**
     * @brief Decodes the MQTT variable header from a byte array
     * @param data The byte array of the packet
     * @param fixedHeader The fixed header of this packet
     * @param offset The current offset of bytes
     * @param varHeaderLength The length of bytes the header is in total
     * @returns An unique pointer to the `MQTTVarHeader` of this packet
     */
    static std::unique_ptr<MQTTVarHeader> decode(  
      const std::vector<uint8_t>& data,
      const MQTTFixedHeader& fixedHeader,
      size_t& offset, 
      size_t& varHeaderLength
    );

    /**
     * @brief Encodes the variable header of this packet to a byte array
     * @returns A byte array of the header
     */
    std::vector<uint8_t> encode() override;


    // Getters

    /// @returns Single byte containing the username, password, will retain, will QOS, will flag and clean session
    uint8_t getFlags() { return m_connectFlags.raw; }

    /// @returns 16-bit timer telling the broker how long to wait before dropping the packet
    uint16_t getKeepAlive() { return m_keepAlive; }

    // Getter helpers

    /// @returns The reserve bit of the flags
    /// @note This will literally always be 0. This function is 100% useless. If you want to call this function just do `x = 0`. It will have the same effect.
    uint8_t getReserved() { return m_connectFlags.reserved; }

    /// @returns If this is a new, clean session
    uint8_t getCleanSession() { return m_connectFlags.cleanSession; }

    /// @returns Does this connect packet have will
    uint8_t getWillFlag() { return m_connectFlags.willFlag; }

    /// @returns When sending the will, which QoS should it have?
    uint8_t getWillQos() { return m_connectFlags.willQoS; }

    /// @returns If the will should be retained after sending
    uint8_t getWillRetain() { return m_connectFlags.willRetain; } 

    /// @returns If the payload contains a password
    uint8_t getPasswordFlag() { return m_connectFlags.passwordFlag; } 

    /// @return If the payload contains an username
    uint8_t getUsernameFlag() { return m_connectFlags.usernameFlag; }


    // Setters

    /// @param cleanSession If this is a new or old session
    void setCleanSession(bool cleanSession) { m_connectFlags.cleanSession = cleanSession; }

    /// @param willFlag If this packet has a will
    void setWillFlag(bool willFlag) { m_connectFlags.willFlag = willFlag; } 

    /// @param willQoS If and what QoS the will has
    void setWillQoS(uint8_t willQoS) { m_connectFlags.willQoS = willQoS; }

    /// @param willRetain If the will should be retained
    void setWillRetain(bool willRetain) { m_connectFlags.willRetain = willRetain; }

    /// @param passwordFlag If the payload contains a password
    void setPasswordFlag(bool passwordFlag) { m_connectFlags.passwordFlag = passwordFlag; }

    /// @param usernameFlag If the client has a username
    void setUsernameFlag(bool usernameFlag) { m_connectFlags.usernameFlag = usernameFlag; }

};


#endif//MQTT_CONNECT_VAR_HEADER