#include "mqtt/broker/mqtt_broker.h"


// Private
std::vector<std::string> MQTTBroker::splitPath(const std::string& path)
{
  std::vector<std::string> result{};
  std::string buffer = "";

  for (char c : path)
  {
    if (c == '/')
    {
      if (!buffer.empty()) result.push_back(buffer);
      buffer = "";
    }
    else
    {
      buffer += c;
    }
  }

  if (!buffer.empty()) result.push_back(buffer);
  return result;
}


// Public
void MQTTBroker::onDataRecieved(uint16_t clientId, const std::vector<uint8_t>& data)
{
  std::unique_ptr<MQTTPacket> packet = MQTTPacket::parse(data);
  if (!packet)
  {
    return;
  }

  switch (packet->getFixedHeader().getType())
  {
    default:
      return;
  }
}


const MQTTNode& MQTTBroker::getNode(const std::string& topicPath)
{
  std::vector<std::string> nodeNames = splitPath(topicPath);

  MQTTNode* currentNode = this;
  for (const std::string& nodeName: nodeNames)
  {
    auto it = currentNode->m_children.find(nodeName);

    if (it == currentNode->m_children.end())
    {
      auto result = currentNode->m_children.emplace(nodeName, MQTTNode(nodeName));
      it = result.first;
    }
    
    currentNode = &(it->second);
  }

  return *currentNode;
}
