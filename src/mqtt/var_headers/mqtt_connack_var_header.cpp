#include "mqtt/var_headers/mqtt_connack_var_header.h"


std::unique_ptr<MQTTVarHeader> MQTTConnackVarHeader::decode(
  const std::vector<uint8_t>& data,
  const MQTTFixedHeader& fixedHeader,
  size_t& offset, 
  size_t& varHeaderLength
)
{
  return nullptr; // TODO: Implement
}


std::vector<uint8_t> MQTTConnackVarHeader::encode()
{
  std::vector<uint8_t> result{};

  result.push_back(getSessionPresent());
  result.push_back(getReturnCode());

  return result;
}