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
#include <sys/poll.h>


using DataCallback = std::function<void(int client_fd, const std::vector<uint8_t>& data)>;

/**
 * @brief A simple class which handles recieving and sending data over the network
*/
class NetworkManager
{
  private:
    int m_port;                             /// The port the server is running on
    int m_server_fd;                        /// The "id" of the server
    int m_buffer_size;                      /// The amount of bytes which can be recieved
    DataCallback m_callback;

    std::atomic<bool> m_running;            /// If the server is running
    std::thread m_worker_thread;            /// The worker thread where everything runs

    std::mutex m_clients_mutex;             /// The clients as a mutex
    std::vector<struct pollfd> m_poll_fds;  /// Weet ik nog niet

    void serverLoop();
    void acceptNewClient();
    void handleClientData(size_t poll_index);


    /**
     * @brief Private constructor in order to follow the singleton pattern
     */
    NetworkManager()
    : m_port(0), m_server_fd(-1), m_buffer_size(4096), m_running(false)
    {}

    /**
     * @brief Deconstructs the network safely by calling `NetworkManager::stop()`
     */
    ~NetworkManager()
    {
      stop();
    }

  public:
    /**
     * @brief Gets the Singleton instance of the NetworkManager
     * @returns A reference to the single NetworkManager instance
     */
    static NetworkManager& getInstance()
    {
      static NetworkManager instance;
      return instance;
    }

    // Delete copy constructor and assignment operator to prevent cloning
    NetworkManager(const NetworkManager&) = delete;
    NetworkManager& operator=(const NetworkManager&) = delete;

    /**
     * @brief Initializes the network manager with its required parameters. Call this before start().
     * @param port The port on which the network manager will listen and send
     * @param callback The callback which will execute when receiving data
     */
    void init(uint16_t port, DataCallback cb)
    {
      m_port = port;
      m_callback = cb;
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

    /**
     * @brief Forcefully disconnects a client and removes them from the polling list
     * @param client_fd The file descriptor of the client to remove
     */
    void removeClient(int client_fd);


    // Getters
    int getBufferSize() { return m_buffer_size; }


    // Setters
    void setBufferSize(int bufferSize) { m_buffer_size = bufferSize; }
  
};


#endif//NETWORK_MANAGER_H