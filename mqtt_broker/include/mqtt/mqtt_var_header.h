#ifndef MQTT_VAR_HEADER_H
#define MQTT_VAR_HEADER_H

#include <string>
#include <stdint>


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
    uint16_t m_packtId;       /// The packet id
    bool m_hasPacketId;       /// Only required when quality of service is 1 or 2

  public:
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


#endif//MQTT_VAR_HEADER_H