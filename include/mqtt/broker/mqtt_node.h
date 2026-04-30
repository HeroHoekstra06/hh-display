#ifndef MQTT_NODE_H
#define MQTT_NODE_H

#include <unordered_map>
#include <vector>


class MQTTNode
{
  private:
    std::string m_topicString;                              /// The name of this topic
    std::unordered_map<std::string, MQTTNode> m_children;   /// The child nodes of this node

  public:
    /**
     * @brief Constructs an MQTTNode which can hold more nodes or subscribed clients
     * @param topicString The name of this topic
     * @note This `topicString` should be the *name* of the topic, not the entire path
     */
    MQTTNode(std::string topicString)
    : m_topicString(topicString)
    {}

};


#endif//MQTT_NODE_H