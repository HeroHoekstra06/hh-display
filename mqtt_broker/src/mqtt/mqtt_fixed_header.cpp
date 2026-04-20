#include "mqtt/mqtt_fixed_header.h"


bool MQTTFixedHeader::isRetained()
{
  return (getType() == Publish) && (m_data.flags & Retain);
}


uint8_t MQTTFixedHeader::getQos()
{
  if (getType() == Publish)
  {
    return (m_data.flags & 0x06) >> 1;
  }
  return 0;
}