#include "network/network_manager.h"

void onDataRecieved(int client_id, const std::vector<uint8_t>& data)
{
  std::cout << "Recieved " << data.size() << " bytes from " << client_id << std::endl;
  
  std::cout << "Bytes data as chars:" << std::endl;
  for (uint8_t byte : data)
  {
    char c = static_cast<char>(byte);
    std::cout << c;
  }
  std::cout << std::endl;
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