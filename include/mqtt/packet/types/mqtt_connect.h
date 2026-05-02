#ifndef MQTT_CONNECT_H
#define MQTT_CONNECT_H

#include <memory>

#include "mqtt/packet/mqtt_packet.h"


class MQTTConnect : public MQTTPacket
{
  private:

  public:
    MQTTConnect(MQTTFixedHeader fixedHeader, std::unique_ptr<MQTTVarHeader> varHeader, MQTTBody body)
    : MQTTPacket(fixedHeader, std::move(varHeader), std::move(body))
    {}

    

};


#endif//MQTT_CONNECT_H