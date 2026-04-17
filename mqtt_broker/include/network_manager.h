#ifndef NETWORK_MANAGER_H
#define NETWORK_MANAGER_H

#include <iostream>
#include <functional>
#include <vector>


using DataCallback = std::function<void(int client_fd, const std::vector<uint8_t>& data)>;

/**
 * @brief A simple class which handles recieving and sending data over the network
*/
class NetworkManager
{
  private:

  public:
    /**
     * @brief Constructs a network manager
     * @param port The port on which the network manager will listen and send
     * @param callback The callback which will execute when recieving data
     */
    NetworkManager(uint8_t port, DataCallback callback);

    /**
     * @brief Deconstructs the network manager safely by calling `NetworkManager::stop()`
     */
    ~NetworkManager();

    /**
     * @brief Starts the network manager and makes it actually listen to incoming requests
     * @returns If it successfully started the manager
     */
    bool start();

    /**
     * @brief Stops the network manager and frees up the port again
    */
    void stop();
};


#endif//NETWORK_MANAGER_H