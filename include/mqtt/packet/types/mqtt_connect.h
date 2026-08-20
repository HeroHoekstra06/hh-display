#ifndef MQTT_CONNECT_H
#define MQTT_CONNECT_H

#include <memory>

#include "mqtt/packet/mqtt_packet.h"


class MQTTConnect : public MQTTPacket
{
  private:
    std::unique_ptr<MQTTConnectVarHeader> m_varHeader;

    std::string m_clientId;           /// The id of the client whom send the packet

    std::string m_username;           /// The username of the client that send the packet
    std::string m_password;           /// The password of the client that send the packet

    std::string m_willTopic;          /// The topic the will will be send to
    std::vector<uint8_t> m_rawWill;   /// The raw bytes of the will
    std::string m_will;               /// The will as a string

  public:
    /**
     * @brief Creates a connect packet from a fixed header, var header and body
     * @param fixedHeader The fixed header of the packet
     * @param varHeader The variable header of the packet
     * @param body The body of the packet
     */
    MQTTConnect(MQTTFixedHeader fixedHeader, std::unique_ptr<MQTTConnectVarHeader> varHeader, MQTTBody body)
    : MQTTPacket(fixedHeader, std::move(varHeader), std::move(body))
    {}

    /**
     * @brief Creates an empty connect packet
     */
    MQTTConnect()
    : MQTTPacket(
      MQTTFixedHeader(),
      std::make_unique<MQTTConnectVarHeader>(0, 0),
      MQTTBody()
    )
    {}


    /**
     * @brief Creates a connect header from an array of bytes
     * @param data The array of bytes of the packet
     * @returns A unique pointer to a connect packet
     */
    static std::unique_ptr<MQTTConnect> parse(const std::vector<uint8_t>& data);


    // Getters

    /// @returns The is of the client
    const std::string& getClientId() { return m_clientId; }

    /// @returns The username of the client
    const std::string& getUsername() { return m_username; }

    /// @returns The password the client send
    const std::string& getPassword() { return m_password; }

    /// @returns The topic the will will be posted to
    const std::string& getWillTopic() { return m_willTopic; }

    /// @returns The bytes of the will in an array
    const std::vector<uint8_t>& getRawWill() { return m_rawWill; }

    /// @returns The will as a string
    const std::string& getWill() { return m_will; }


    // Setters

    /// @param id The id of the client
    void setClientId(const std::string& id) { m_clientId = id; }

    /// @param username The username of the client
    /// @note Will also set the username flag in the variable header
    void setUsername(const std::string& username) 
    { 
      m_varHeader->setUsernameFlag(username.size() > 0);
      m_username = username; 
    }

    /// @param password The password the client has submitted
    /// @note Will also set the password flag in the variable header
    void setPassword(const std::string& password) 
    { 
      m_varHeader->setPasswordFlag(password.size() > 0);
      m_password = password; 
    }

    /// @param willTopic The topic the will message will be send to when client disconnect unexpectedly
    /// @note Will set the will flag in the variable header IF the will topic is not empty. 
    /// If this is not set/the string is empty, it is assumed there is no will
    void setWillTopic(const std::string& willTopic) 
    {
      m_varHeader->setWillFlag(!willTopic.empty());
      m_willTopic = willTopic;
    }

    /// @param rawWill The raw will as a byte array
    /// @note Will also set the string will
    void setRawWill(const std::vector<uint8_t>& rawWill) 
    {
      m_rawWill = rawWill;
      m_will = std::string(rawWill.begin(), rawWill.end());
    }

    /// @param will The will as a string
    /// @note Will also set the raw will
    void setWill(const std::string& will) {
      m_will = will;
      m_rawWill = std::vector<uint8_t>(will.begin(), will.end());
    }


    // Variable header getters (helpers)

    /// @returns If this is a new, clean session
    /// @note This is a helper function and will return `getCleanSession()` from this object's variable header
    uint8_t getCleanSession() { return m_varHeader->getCleanSession(); }

    /// @returns Does this connect packet have will
    /// @note This is a helper function and will return `getWillFlag()` from this object's variable header
    uint8_t getWillFlag() { return m_varHeader->getWillFlag(); }

    /// @returns When sending the will, which QoS should it have?
    /// @note This is a helper function and will return `getWillQos()` from this object's variable header
    uint8_t getWillQos() { return m_varHeader->getWillQos(); }

    /// @returns If the will should be retained after sending
    /// @note This is a helper function and will return `getWillRetain()` from this object's variable header
    uint8_t getWillRetain() { return m_varHeader->getWillRetain(); } 

    /// @returns If the payload contains a password
    /// @note This is a helper function and will return `getPasswordFlag()` from this object's variable header
    uint8_t getPasswordFlag() { return m_varHeader->getPasswordFlag(); } 

    /// @return If the payload contains an username
    /// @note This is a helper function and will return `getUsernameFlag()` from this object's variable header
    uint8_t getUsernameFlag() { return m_varHeader->getUsernameFlag(); }

    // Variable header setters (helpers)

    /// @param cleanSession If this is a new or old session
    /// @note This is a helper function and will call `setCleanSession(bool)` from this object's variable header
    void setCleanSession(bool cleanSession) { m_varHeader->setCleanSession(cleanSession); }

    /// @param willFlag If this packet has a will
    /// @note This is a helper function and will call `setWillFlag(bool)` from this object's variable header
    void setWillFlag(bool willFlag) { m_varHeader->setWillFlag(willFlag); } 

    /// @param willQoS If and what QoS the will has
    /// @note This is a helper function and will call `setWillQos(uint8_t)` from this object's variable header
    void setWillQoS(uint8_t willQoS) { m_varHeader->setWillQoS(willQoS); }

    /// @param willRetain If the will should be retained
    /// @note This is a helper function and will call `setWillRetain(bool)` from this object's variable header
    void setWillRetain(bool willRetain) { m_varHeader->setWillRetain(willRetain); }

    /// @param passwordFlag If the payload contains a password
    /// @note This is a helper function and will call `setPasswordFlag(bool)` from this object's variable header
    void setPasswordFlag(bool passwordFlag) { m_varHeader->setPasswordFlag(passwordFlag); }

    /// @param usernameFlag If the client has a username
    /// @note This is a helper function and will call `setUsernameFlag(bool)` from this object's variable header
    void setUsernameFlag(bool usernameFlag) { m_varHeader->setUsernameFlag(usernameFlag); }
};


#endif//MQTT_CONNECT_H