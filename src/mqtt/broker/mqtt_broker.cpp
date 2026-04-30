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
      result.push_back(buffer);
      buffer = "";
    }
    else
    {
      buffer += c;
    }
  }

  return result;
}


// Public
const MQTTNode& MQTTBroker::getNode(const std::string& topicPath)
{
}