#include "mqtt/var_headers/mqtt_connect_var_header.h"


std::unique_ptr<MQTTVarHeader> MQTTConnectVarHeader::decode(
  const std::vector<uint8_t>& data,
  const MQTTFixedHeader& fixedHeader,
  size_t& offset, 
  size_t& varHeaderLength
)
{
  if (offset > data.size())
  { 
    return nullptr;
  }
  uint16_t protoLen = (data[offset] << 8 | data[offset + 1]);
  offset += 2;

  if (offset + protoLen > data.size())
  { 
    return nullptr;
  }
  offset += protoLen;

  if (offset + 4 > data.size()) 
  {
    return nullptr;
  }

  uint8_t level = data[offset++];
  uint8_t flags = data[offset++];
  uint16_t keepAlive = (data[offset] << 8 | data[offset + 1]);

  varHeaderLength = 2 + protoLen + 4;
  return std::make_unique<MQTTConnectVarHeader>(flags, keepAlive, level);
}


std::vector<uint8_t> MQTTConnectVarHeader::encode()
{
  std::vector<uint8_t> result{};

  result.push_back(0x00);
  result.push_back(0x04);

  std::string protocolName = "MQTT";
  for (char c : protocolName) result.push_back(c);

  result.push_back(4);
  result.push_back(static_cast<uint8_t>(getFlags()));

  uint16_t keepAlive = getKeepAlive();
  result.push_back((keepAlive >> 8) & 0xFF);
  result.push_back(keepAlive & 0xFF);

  return result;
}
