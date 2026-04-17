#ifndef NETWORK_MANAGER_H
#define NETWORK_MANAGER_H

#include <iostream>
#include <string>
#include <vector>
#include <functional>
#include <thread>
#include <atomic>
#include <mutex>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <poll.h>


using DataCallback = std::function<void(int client_fd, const std::vector<uint8_t>& data)>;

/**
 * @brief A simple class which handles recieving and sending data over the network
*/
class NetworkManager
{
  private:
    int m_port;                             /// The port the server is running on
    int m_server_fd;                        /// The "id" of the server
    DataCallback m_callback;

    std::atomic<bool> m_running;            /// If the server is running
    std::thread m_worker_thread;            /// The worker thread where everything runs

    std::mutex m_clients_mutex;             /// The clients as a mutex
    std::vector<struct pollfd> m_poll_fds;  /// Weet ik nog niet

    void serverLoop();
    void acceptNewClient();
    void handleClientData(size_t poll_index);
    void removeClient();

  public:
    /**
     * @brief Constructs a network manager
     * @param port The port on which the network manager will listen and send
     * @param callback The callback which will execute when recieving data
     */
    NetworkManager(int port, DataCallback callback)
    : m_port(port), m_callback(callback), m_running(false), m_server_fd(-1)
    {}

    /**
     * @brief Deconstructs the network manager safely by calling `NetworkManager::stop()`
     */
    ~NetworkManager()
    {
      stop();
    }

    /**
     * @brief Starts the network manager and makes it actually listen to incoming requests
     * @returns If it successfully started the manager
     */
    bool start();

    /**
     * @brief Stops the network manager and frees up the port again
    */
    void stop();

    /**
     * @brief Sends a payload to a specific client
     * @param client_id A specific client
     * @param data A list of bytes represented by `uint8_t`
     * @returns If the data was successfully send
     */
    bool sendData(int client_fd, const std::vector<uint8_t>& data);
  
};


#endif//NETWORK_MANAGER_H