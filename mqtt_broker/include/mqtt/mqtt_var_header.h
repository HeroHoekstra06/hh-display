#ifndef MQTT_VAR_HEADER_H
#define MQTT_VAR_HEADER_H

#include <string>
#include <stdint.h>


/**
 * @brief Basic MQTT variable header super class
*/
class MQTTVarHeader
{
  public:
    virtual ~MQTTVarHeader() = default;
};


class MQTTPublishVarHeader : public MQTTVarHeader
{
  private:
    std::string m_topicName;  /// The topic name the packet is meant for
    uint16_t m_packetId;      /// The packet id
    bool m_hasPacketId;       /// Only required when quality of service is 1 or 2

  public:
    /**
     * @brief Creates a variable header used for posting to the broker
     * @param topic The designated topic
     * @param packetId The id of packet
     * @param hasPacketId If the packet even has an id
     * @note `hasPacketId` is only needed when QOS is 1 or 2
     */
    MQTTPublishVarHeader(std::string topic, uint16_t packetId = 0, bool hasPacketId = false)
    : m_topicName(topic), m_packetId(packetId), m_hasPacketId(hasPacketId)
    {}


    // Getters
    /// @returns The name of the topic the packet is meant for
    const std::string& getTopicName() const { return m_topicName; }

    /// @returns The id of the packet
    uint16_t getPacketId() { return m_packetId; }

    /// @returns If the packet has a packet id, only when the QOS is 1 or 2
    bool getHasPacketId() { return m_hasPacketId; }

};


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


#endif//MQTT_VAR_HEADER_H