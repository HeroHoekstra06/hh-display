#include "network_manager.h"

#include <cstring>
#include <algorithm>


bool NetworkManager::start()
{
  m_server_fd = socket(AF_INET, SOCK_STREAM, 0);
  if (m_server_fd == 0)
  {
    std::cerr << "Socket creation failed" << std::endl;
    return false;
  }

  int opt = 1;
  setsockopt(m_server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

  struct sockaddr_in address;
  address.sin_family = AF_INET;
  address.sin_addr.s_addr = INADDR_ANY;
  address.sin_port = htons(m_port);

  if (bind(m_server_fd, (struct sockaddr*)&address, sizeof(address)) < 0)
  {
    std::cerr << "Could not bind socket" << std::endl;
    close(m_server_fd);
    return false;
  }

  if (listen(m_server_fd, 10) < 0)
  {
    std::cerr << "Could not start listening" << std::endl;
    close(m_server_fd);
    return false;
  }

  struct pollfd server_poll_fd;
  server_poll_fd.fd = m_server_fd;
  server_poll_fd.events = POLLIN;
  m_poll_fds.push_back(server_poll_fd);

  m_running = true;
  m_worker_thread = std::thread(&NetworkManager::serverLoop, this);

  std::cout << "Started listening on port '" << m_port << "'" << std::endl;
  return true;
}

void NetworkManager::stop()
{
  if (m_running)
  {
    m_running = false;
    if (m_worker_thread.joinable())
    {
      m_worker_thread.join();
    }

    std::lock_guard<std::mutex> lock(m_clients_mutex);
    for (auto& pfd : m_poll_fds)
    {
      close(pfd.fd);
    }
    m_poll_fds.clear();
  }
}

bool NetworkManager::sendData(int client_fd, const std::vector<uint8_t>& data)
{
  ssize_t bytes_sent = send(client_fd, data.data(), data.size(), 0);
  return bytes_sent == static_cast<ssize_t>(data.size());
}
