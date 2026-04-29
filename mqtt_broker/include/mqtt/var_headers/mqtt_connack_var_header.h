#ifndef MQTT_CONNACK_VAR_HEADER
#define MQTT_CONNACK_VAR_HEADER

#include "mqtt/var_headers/mqtt_var_header.h"


class MQTTConnackVarHeader : public MQTTConnackVarHeader
{
  private:
    uint8_t m_sessionPresent;   /// Flag to tell the client if a previous session was found
    uint8_t m_returnCode;       /// The return code of the connect request (0 means connected)

  public:
    /**
     * @brief Creates a variable header used for acknowlodging a connection
     * @param returnCode 0 for a successfull connection, anything else for "failed"
     * @param sessionPresent 1 if resuming a previous session, 0 for a clean session
     */
    MQTTConnackVarHeader(uint8_t returnCode, uint8_t sessionPresent = 0)
    : m_sessionPresent(sessionPresent), m_returnCode(returnCode)
    {}


    // Getters
    /// @returns A flag to tell if the client connected to an already existing session
    uint8_t getSessionPresent() { return m_sessionPresent; }

    /// @returns A code to tell the client if the connection was a success
    uint8_t getReturnCode() { return m_returnCode; }

}


#endif//MQTT_CONNACK_VAR_HEADER