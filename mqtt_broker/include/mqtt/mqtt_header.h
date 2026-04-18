#ifndef MQTT_HEADER_H
#define MQTT_HEADER_H

#include  <stdint.h>


class MQTTHeader
{
  private:
    union
    {
      uint8_t raw;
      struct
      {
        uint8_t flags : 4;  /// Second nibble (LSB)
        uint8_t type  : 4;  /// First nibble (MSB)
      };
    } m_data;                 /// The request header data
    
  public:
    /**
     * @brief Constructs an empty MQTTHeader
     */
    MQTTHeader() { m_data.raw = 0; }

    /**
     * @brief Constructs an MQTTHeader with flag and type data
     * @param byte The byte which says what type and flag this packet has
     */
    MQTTHeader(uint8_t byte) { m_data.raw = byte; }

    
    // Getters
    /// @returns The type of the request
    uint8_t getType() { return m_data.type; }

    /// @returns The flags of the request
    uint8_t getFlags() { return m_data.flags; }

};


#endif//MQTT_HEADER_H