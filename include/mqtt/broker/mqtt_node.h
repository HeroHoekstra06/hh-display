#ifndef MQTT_NODE_H
#define MQTT_NODE_H

#include <unordered_map>
#include <vector>

#include "mqtt/broker/mqtt_client.h"


class MQTTNode
{
  protected:
    std::string m_topicString;                              /// The name of this topic
    std::unordered_map<std::string, MQTTNode> m_children;   /// The child nodes of this node

    std::vector<MQTTClient*> m_subscribers;                 /// All clients who are subscribed THIS node
    std::vector<MQTTClient*> m_childSubscribers;            /// All clients who are subscribed to this node's children
    std::vector<MQTTClient*> m_generalSubscribers;          /// All clients who are subscribed to all this node's children

  public:
    /**
     * @brief Constructs an MQTTNode which can hold more nodes or subscribed clients
     * @param topicString The name of this topic
     * @note This `topicString` should be the *name* of the topic, not the entire path
     */
    MQTTNode(std::string topicString)
    : m_topicString(topicString), m_children({}), 
      m_subscribers({}), m_childSubscribers({}), m_generalSubscribers({})
    {}

};


#endif//MQTT_NODE_H