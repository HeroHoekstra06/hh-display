#include "mqtt/broker/mqtt_node.h"


void MQTTNode::subscribe(std::shared_ptr<MQTTClient> client)
{
  m_subscribers.push_back(client);
}
