#ifndef MQTT_CONNECT_BODY
#define MQTT_CONNECT_BODY

#include "mqtt_body.h"


class MQTTConnectBody : public MQTTBody 
{
  private:

  public:
    /**
     * @brief Creates an empty body
     */
    MQTTConnectBody() = default;

    /**
     * @brief Creates a body with data
     * @param payload A list of bytes
     */
    MQTTConnectBody(const std::vector<uint8_t>& payload)
    : MQTTBody(payload)
    {
      
    }
  
};


#endif//MQTT_CONNECT_BODY