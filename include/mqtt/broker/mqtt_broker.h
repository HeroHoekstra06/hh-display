#ifndef MQTT_BROKER_H
#define MQTT_BROKER_H

#include <memory>
#include <string>
#include <vector>
#include <unordered_map>

#include "mqtt/broker/mqtt_node.h"


class MQTTBroker : public MQTTNode
{
  private:
    std::unordered_map<int, std::shared_ptr<MQTTClient>> m_clients;    /// All clients who are currently connected


    /**
     * @brief Splits a string into a string array
     * @param path The raw string path
     * @returns The path to a nod, where each node is split by a '/'
     */
    std::vector<std::string> splitPath(const std::string& path);

    /**
     * @brief Adds a new client to the client list
     * @param client The client to be added
     */
    void addClient(const MQTTClient& client);

    /**
     * @brief Removes a client by id
     * @param clientId The client to be removed
     */
    void removeClient(int clientId);
    
    // Responses
    void connectResponse(int clientId, std::unique_ptr<MQTTPacket> packet);

  public:
    /**
     * @brief Constructs an MQTTBroker, which is just a fancy MQTTNode
     */
    MQTTBroker()
    : MQTTNode("")
    {}


    /**
     * @brief Handles and call functions according to the packet recieved
     * @param clientId The id of the client who send the packet
     * @param data The data as a byte array
     */
    void onDataRecieved(int clientId, const std::vector<uint8_t>& data);

    /**
     * @brief Gets or creates an MQTT topic
     * @param topicPath The path to the topic. Nodes are sepperated by '/'.
     * @returns The MQTTNode which contains the clients subscribed (directly and indirectly)
     */
    const MQTTNode& getNode(const std::string& topicPath);

};


#endif//MQTT_BROKER_H