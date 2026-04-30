#ifndef MQTT_NODE_H
#define MQTT_NODE_H

#include <memory>
#include <unordered_map>
#include <vector>

#include "mqtt/broker/mqtt_client.h"


class MQTTNode
{
  friend class MQTTBroker;

  protected:
    std::string m_topicString;                              /// The name of this topic
    std::unordered_map<std::string, MQTTNode> m_children;   /// The child nodes of this node
    std::vector<std::weak_ptr<MQTTClient>> m_subscribers;   /// All clients who are subscribed this node

  public:
    /**
     * @brief Constructs an MQTTNode which can hold more nodes or subscribed clients
     * @param topicString The name of this topic
     * @note This `topicString` should be the *name* of the topic, not the entire path
     */
    MQTTNode(std::string topicString)
    : m_topicString(topicString), m_children({}), m_subscribers({})
    {}


    /**
     * @brief Adds a client to be informed of all updates to this topic
     * @param client The shared pointer to add
    */
    void subscribe(std::shared_ptr<MQTTClient> client);

};


#endif//MQTT_NODE_H