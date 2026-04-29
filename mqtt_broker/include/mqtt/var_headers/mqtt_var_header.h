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
     * @brief Encodes the variable header of this packet to a byte array
     * @returns A byte array of the header
     */
    virtual std::vector<uint8_t> encode() = 0;
};


#endif//MQTT_VAR_HEADER