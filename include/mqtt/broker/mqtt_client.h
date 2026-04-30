#ifndef MQTT_CLIENT_H
#define MQTT_CLIENT_H

#include <stdint.h>
#include <string>


class MQTTClient
{
  private:
    uint16_t m_clientId;        /// The client ID according to the network manager
    std::string m_clientName;   /// The client ID according to the client

  public:
    /**
     * @brief Creates a client which can later be used to subscribe to topics
     * @param clientName The id the client has given us
     * @param clientId The id assigned by the network manager
     */
    MQTTClient(const std::string& clientName, uint16_t clientId)
    : m_clientId(clientId), m_clientName(std::move(clientName))
    {}

};


#endif//MQTT_CLIENT_H