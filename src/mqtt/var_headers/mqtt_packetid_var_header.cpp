#include "mqtt/var_headers/mqtt_packetid_var_header.h"


std::unique_ptr<MQTTVarHeader> MQTTPacketIdVarHeader::decode(
  const std::vector<uint8_t>& data,
  const MQTTFixedHeader& fixedHeader, // Can be a nullptr, as it is not used but must be here for "inheritance purposes"
  size_t& offset, 
  size_t& varHeaderLength
)
{
  if (offset + 2 > data.size())
  { 
    return nullptr;
  }

  uint16_t packetId = (data[offset] << 8 | data[offset + 1]);
  varHeaderLength = 2;

  return std::make_unique<MQTTPacketIdVarHeader>(packetId);
}


std::vector<uint8_t> MQTTPacketIdVarHeader::encode()
{
  std::vector<uint8_t> result{};

  uint16_t pid = getPacketId();
  result.push_back((pid >> 8) & 0xFF);
  result.push_back(pid & 0xFF);

  return result;
}
