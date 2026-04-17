#include "network_manager.h"

void onDataRecieved(int client_id, const std::vector<uint8_t>& data)
{
  std::cout << "Recieved " << data.size() << " bytes from " << client_id << std::endl;
  // TODO: Parse bytes
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