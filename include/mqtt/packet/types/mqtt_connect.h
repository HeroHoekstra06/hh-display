#ifndef MQTT_CONNECT_H
#define MQTT_CONNECT_H

#include <memory>

#include "mqtt/packet/mqtt_packet.h"


class MQTTConnect : public MQTTPacket
{
  private:

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

};


#endif//MQTT_CONNECT_H