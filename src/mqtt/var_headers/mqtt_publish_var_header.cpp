#include "mqtt/var_headers/mqtt_publish_var_header.h"


std::unique_ptr<MQTTVarHeader> MQTTPublishVarHeader::decode(
  const std::vector<uint8_t>& data,
  const MQTTFixedHeader& fixedHeader,
  size_t& offset, 
  size_t& varHeaderLength
)
{
  if (offset + 2 > data.size())
  {
    return nullptr;
  }
  uint16_t topicLen = (data[offset] << 8 | data[offset + 1]);
  offset += 2;

  if (offset + topicLen > data.size())
  {
    return nullptr;
  }
  std::string topic(data.begin() + offset, data.begin() + offset + topicLen);
  offset += topicLen;
  varHeaderLength = 2 + topicLen;

  uint16_t packetId = 0;
  bool hasPacketId = fixedHeader.getQos() > 0;

  if (hasPacketId)
  {
    if (offset + 2 > data.size())
    {
      return nullptr;
    }
    packetId = (data[offset] << 8 | data[offset + 1]);
    varHeaderLength += 2;
    offset += 2;
  }

  return std::make_unique<MQTTPublishVarHeader>(topic, packetId, hasPacketId);
}


std::vector<uint8_t> MQTTPublishVarHeader::encode()
{
  std::vector<uint8_t> result{};

  uint16_t topicLen = getTopicName().length();
  result.push_back((topicLen >> 8) & 0xFF);
  result.push_back(topicLen & 0xFF);

  for (char c : getTopicName()) result.push_back(c);

  if (getHasPacketId())
  {
    uint16_t pid = getPacketId();
    result.push_back((pid >> 8) & 0xFF);
    result.push_back(pid & 0xFF);
  }

  return result;
}
