#ifndef MQTT_VAR_HEADER_H
#define MQTT_VAR_HEADER_H

#include <string>
#include <stdint.h>
#include <vector>
#include <memory>

#include "mqtt/mqtt_fixed_header.h"


/**
 * @brief Basic MQTT variable header super class
*/
class MQTTVarHeader
{
  public:
    virtual ~MQTTVarHeader() = default;

    /**
     * @brief Decodes the MQTT variable header from a byte array
     * @param data The byte array of the packet
     * @param fixedHeader The fixed header of this packet
     * @param offset The current offset of bytes
     * @param varHeaderLength The length of bytes the header is in total
     * @returns An unique pointer to the `MQTTVarHeader` of this packet
     */
    virtual std::unique_ptr<MQTTVarHeader> decode(
      const std::vector<uint8_t>& data,
      const MQTTFixedHeader& fixedHeader,
      size_t& offset, 
      size_t& varHeaderLength
    );
    
    /**
     * @brief Encodes the variable header of this packet to a byte array
     * @returns A byte array of the header
     */
    virtual std::vector<uint8_t> encode();
};


#endif//MQTT_VAR_HEADER