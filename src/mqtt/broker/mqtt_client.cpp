#include "mqtt/broker/mqtt_client.h"

#include "network/network_manager.h"


bool MQTTClient::sendPacket(MQTTPacket packet)
{
  std::vector<uint8_t> rawPacket = packet.serialize();
  return NETWORK_MANAGER.sendData(m_clientId, rawPacket);
}
