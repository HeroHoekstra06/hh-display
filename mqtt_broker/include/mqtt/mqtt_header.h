#ifndef MQTT_HEADER_H
#define MQTT_HEADER_H

#include  <stdint.h>


enum MQTTHeaderType : uint8_t
{
  Connect = 1,
  Connack = 2,
  Publish = 3,
  Puback = 4,
  Pubrec = 5,
  Pubcomp = 7,
  Subscribe = 8,
  Suback = 9,
  Unsubscribe = 10,
  Unsuback = 11,
  Pingreq = 12,
  Pingresp = 13,
  Disconnect = 14,
  Auth = 15
};


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
    MQTTHeaderType getType() { return static_cast<MQTTHeaderType>(m_data.type); }

    /// @returns The flags of the request
    uint8_t getFlags() { return m_data.flags; }

};


#endif//MQTT_HEADER_H