#ifndef MQTT_PUBLISH_VAR_HEADER
#define MQTT_PUBLISH_VAR_HEADER

#include <stdint.h>
#include <string>

#include "mqtt/packet/var_headers/mqtt_var_header.h"


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
    /// @returns The name of the topic the packet is meant for
    const std::string& getTopicName() const { return m_topicName; }

    /// @returns The id of the packet
    uint16_t getPacketId() { return m_packetId; }

    /// @returns If the packet has a packet id, only when the QOS is 1 or 2
    bool getHasPacketId() { return m_hasPacketId; }

};


#endif//MQTT_PUBLISH_VAR_HEADER