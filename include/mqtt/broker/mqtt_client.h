#ifndef MQTT_CLIENT_H
#define MQTT_CLIENT_H

#include <stdint.h>
#include <string>

#include "mqtt/packet/mqtt_packet.h"
#include "network/network_manager.h"

#define NETWORK_MANAGER NetworkManager::getInstance()


class MQTTClient
{
  private:
    int m_clientId;        /// The client ID according to the network manager
    std::string m_clientName;   /// The client ID according to the client

  public:
    /**
     * @brief Creates a client which can later be used to subscribe to topics
     * @param clientName The id the client has given us
     * @param clientId The id assigned by the network manager
     */
    MQTTClient(const std::string& clientName, int clientId)
    : m_clientId(clientId), m_clientName(std::move(clientName))
    {}


    bool sendPacket(MQTTPacket packet);


    // Getters
    /// @returns The id of the client
    int getClientId() const { return m_clientId; }

};


#endif//MQTT_CLIENT_H