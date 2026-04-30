#ifndef MQTT_BROKER_H
#define MQTT_BROKER_H

#include <unordered_map>

#include "mqtt/broker/mqtt_node.h"


class MQTTBroker : public MQTTNode
{
  private:
    

  public:
    /**
     * @brief Constructs an MQTTBroker, which is just a fancy MQTTNode
     */
    MQTTBroker()
    : MQTTNode("")
    {}


    /**
     * @brief Gets a topic node according to the topic path
     * @param topicPath The path to the topic. Nodes are sepperated by '/'.
     * @returns The MQTTNode which contains the clients subscribed (directly and indirectly)
     */
    const MQTTNode& getNode(const std::string& topicPath);

};


#endif//MQTT_BROKER_H