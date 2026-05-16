#include "mqtt/packet/types/mqtt_connect.h"


std::unique_ptr<MQTTConnect> MQTTConnect::parse(const std::vector<uint8_t>& data)
{
  std::unique_ptr<MQTTPacket> basePacket = MQTTPacket::parse(data);
  if (!basePacket)
  {
    return nullptr;
  }

  if (basePacket->getFixedHeader().getType() != Connect)
  {
    return nullptr;
  }
  
  auto& varHeaderRef = const_cast<std::unique_ptr<MQTTVarHeader>&>(basePacket->getVarHeader());
  auto connectPacket = std::make_unique<MQTTConnect>(
    basePacket->getFixedHeader(), 
    std::move(varHeaderRef), 
    basePacket->getBody() 
  );

  return connectPacket;
}
