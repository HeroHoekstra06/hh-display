#include "network/network_manager.h"
#include "mqtt/mqtt_packet.h"

void onDataRecieved(int client_id, const std::vector<uint8_t>& data)
{
  std::cout << "Recieved " << data.size() << " bytes from " << client_id << std::endl;
  
  std::unique_ptr<MQTTPacket> packet = MQTTPacket::parse(data);
  if (!packet)
  {
    std::cerr << "Error: Could not parse packet" << std::endl;
    return;
  }

  const MQTTBody& body = packet->getBody();
  std::cout << body.getString() << std::endl;
}

int main()
{
  NetworkManager manager{1883, onDataRecieved};

  if (manager.start())
  {
    while (true)
    {
      std::this_thread::sleep_for(std::chrono::seconds(1));
    }
  }

  return 0;
}