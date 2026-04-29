#include "network/network_manager.h"
#include "mqtt/mqtt_packet.h"

#define NETWORK_MANAGER NetworkManager::getInstance()


void onDataRecieved(int client_id, const std::vector<uint8_t>& data)
{
  std::cout << "Recieved " << data.size() << " bytes from " << client_id << std::endl;
  
  std::unique_ptr<MQTTPacket> packet = MQTTPacket::parse(data);
  if (!packet)
  {
    std::cerr << "Error: Could not parse packet" << std::endl;
    return;
  }

  std::cout << packet->getBody().getString() << std::endl;

  if (packet->getFixedHeader().getType() == Connect)
  {
    // Create Connack Header
    MQTTFixedHeader fixedHeader{(Connack << 4) | 0x00, 2};
    auto varHeader = std::make_unique<MQTTConnackVarHeader>(0);
    MQTTBody body;

    MQTTPacket packet{fixedHeader, std::move(varHeader), std::move(body)};
    auto rawBytes = packet.serialize();

    NETWORK_MANAGER.sendData(client_id, rawBytes);
  }
}

int main()
{
  NETWORK_MANAGER.init(1883, onDataRecieved);

  if (NETWORK_MANAGER.start())
  {
    while (true)
    {
      std::this_thread::sleep_for(std::chrono::seconds(1));
    }
  }

  return 0;
}