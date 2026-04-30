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


void MQTTBroker::addClient(const MQTTClient& client)
{
  // Make the client aware that they have been added
  uint8_t code = 0x00;
  uint8_t sessionPresent = 0;

  MQTTFixedHeader fixedHeader{0x20, Connack};
  auto varHeader = std::make_unique<MQTTConnackVarHeader>(code, sessionPresent);
  MQTTBody body;

  MQTTPacket returnPacket{fixedHeader, std::move(varHeader), std::move(body)};
  auto rawPacket = returnPacket.serialize();
  NETWORK_MANAGER.sendData(client.getClientId(), rawPacket);

  auto sharedClient = std::make_shared<MQTTClient>(client);
  m_clients.emplace(client.getClientId(), std::move(sharedClient));
}


void MQTTBroker::removeClient(int clientId)
{
  auto it = m_clients.find(clientId);
  if (it != m_clients.end())
  {
    m_clients.erase(it);
  }

  NETWORK_MANAGER.removeClient(clientId);
}


void MQTTBroker::connectResponse(int clientId, std::unique_ptr<MQTTPacket> packet)
{
  // Right now, we are not checking for any authentication (e.g. password and username, auth, protocol, etc.)
  // TODO: Do add that. ^^^
  std::string payload = packet->getBody().getString();
  MQTTClient client{payload, clientId};

  addClient(client);
}


// Public
void MQTTBroker::onDataRecieved(int clientId, const std::vector<uint8_t>& data)
{
  std::unique_ptr<MQTTPacket> packet = MQTTPacket::parse(data);
  if (!packet)
  {
    return;
  }

  switch (packet->getFixedHeader().getType())
  {
    case Connect:
    {
      connectResponse(clientId, std::move(packet));
      break;
    }

    case Connack:
    case Suback:
    case Unsuback:
    case Pingresp:
    {
      // These are all responses only a broker should send
      // Since we are the broker, according to official specs, we should drop the client
      removeClient(clientId);
      break;
    }

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
