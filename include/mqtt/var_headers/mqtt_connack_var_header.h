#ifndef MQTT_CONNACK_VAR_HEADER
#define MQTT_CONNACK_VAR_HEADER

#include "mqtt/var_headers/mqtt_var_header.h"


class MQTTConnackVarHeader : public MQTTVarHeader
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


    /**
     * @brief Decodes the MQTT variable header from a byte array
     * @param data The byte array of the packet
     * @param fixedHeader The fixed header of this packet
     * @param offset The current offset of bytes
     * @param varHeaderLength The length of bytes the header is in total
     * @returns An unique pointer to the `MQTTVarHeader` of this packet
     */
    static std::unique_ptr<MQTTVarHeader> decode(
      const std::vector<uint8_t>& data,
      const MQTTFixedHeader& fixedHeader,
      size_t& offset, 
      size_t& varHeaderLength
    );

    /**
     * @brief Encodes the variable header of this packet to a byte array
     * @returns A byte array of the header
     */
    std::vector<uint8_t> encode() override;


    // Getters
    /// @returns A flag to tell if the client connected to an already existing session
    uint8_t getSessionPresent() { return m_sessionPresent; }

    /// @returns A code to tell the client if the connection was a success
    uint8_t getReturnCode() { return m_returnCode; }

};


#endif//MQTT_CONNACK_VAR_HEADER