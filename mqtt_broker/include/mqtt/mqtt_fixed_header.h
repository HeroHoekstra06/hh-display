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
  Pubrel = 6,
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

enum MQTTPublishFlags : uint8_t
{
  Retain = 0x01,
  QOS_0 = 0x00,
  QOS_1 = 0x02,
  QOS_2 = 0x04,
  Dup = 0x08
};


class MQTTFixedHeader
{
  private:
    union
    {
      uint8_t raw;
      struct
      {
        uint8_t flags : 4;    /// Second nibble (LSB)
        uint8_t type  : 4;    /// First nibble (MSB)
      };
    } m_data;                 /// The request header data

    uint32_t m_contentLength;  /// The length of the Variable Header and Payload
    
  public:
    /**
     * @brief Constructs an empty `MQTTFixedHeader`
     */
    MQTTFixedHeader() { m_data.raw = 0; }

    /**
     * @brief Constructs a fixed header with flag and type data
     * @param byte The byte which says what type and flag this packet has
     * @param contentLength The amount of bytes in the variable header and payload of the packet
     */
    MQTTFixedHeader(uint8_t byte, uint32_t contentLength) 
    : m_contentLength(contentLength)
    { m_data.raw = byte; }


    /**
     * @brief Checks if the packet is retained
     * @returns If the packet is retained
     */
    bool isRetained()
    {
      return (getType() == Publish) && (m_data.flags & Retain);
    }

    /**
     * @brief Gets the quality of service of the packet
     * @returns The QOS
     */
    uint8_t getQos()
    {
      if (getType() == Publish)
      {
        return (m_data.flags & 0x06) >> 1;
      }
      return 0;
    }

    
    // Getters
    /// @returns The type of the request
    MQTTHeaderType getType() { return static_cast<MQTTHeaderType>(m_data.type); }

    /// @returns The flags of the request
    MQTTPublishFlags getFlags() { return static_cast<MQTTPublishFlags>(m_data.flags); }

};


#endif//MQTT_HEADER_H