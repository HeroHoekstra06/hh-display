#ifndef MQTT_BODY_H
#define MQTT_BODY_H

#include <vector>
#include <stdint.h>


class MQTTBody
{
  private:
    std::vector<uint8_t> m_payload;

  public:
    /**
     * @brief Creates an empty body
     */
    MQTTBody() = default;

    /**
     * @brief Creates a body with data
     * @param payload A list of bytes
     */
    MQTTBody(const std::vector<uint8_t>& payload)
    : m_payload(payload)
    {}

    /**
     * @brief Creates a body with data
     * @param payload A list of bytes
     */
    MQTTBody(std::vector<uint8_t>&& payload)
    : m_payload(std::move(payload))
    {}


    // Getters
    /// @returns The raw payload
    const std::vector<uint8_t>& getPayload() { return m_payload; }

    /// @returns The amount of bytes in the payload
    size_t getSize() { return m_payload.size(); }

    /// @returns If the payload is empty
    bool isEmpty() { return m_payload.empty(); }

};


#endif//MQTT_BODY_H