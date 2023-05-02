#ifndef UDPSERVER_HPP
#define UDPSERVER_HPP

#include <arpa/inet.h>
#include <array>
#include <bits/iterator_concepts.h>
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <netinet/in.h>
#include <stdexcept>
#include <sys/socket.h>
#include <type_traits>
#include <unistd.h>
#include <vector>

namespace Zen::Net {

static constexpr std::size_t DEFAULT_BUFFER_SIZE = 1024;

template <std::size_t BufferSize = DEFAULT_BUFFER_SIZE,
          typename PortT = std::uint16_t>
class UDPServ {
private:
  // TODO(markovejnovic): Incorrect array size, should use the template.
  using OnDataCallback = void(std::array<std::byte, 1024>::iterator begin,
                              std::array<std::byte, 1024>::iterator end);

public:
  UDPServ(const PortT port, OnDataCallback onDataReceived)
      : m_servAddr({.sin_family = AF_INET,
                    .sin_port = htons(port),
                    .sin_addr = {.s_addr = INADDR_ANY}}),
        m_fd(socket(AF_INET, SOCK_DGRAM, 0)),
        m_onReceivedCallback(onDataReceived) {
    if (m_fd < 0) {
      throw std::runtime_error("Could not initialize the socket");
    }

    if (bind(m_fd, reinterpret_cast<struct sockaddr *>(&m_servAddr),
             sizeof(m_servAddr)) < 0) {
      throw std::runtime_error("Could not bind to the socket.");
    }
  }

  void Begin() {
    while (true) {
      struct sockaddr_in clientAddr = {0};
      socklen_t clientAddrLen = {0};

      const size_t nBytes = recvfrom(
          m_fd, m_inBuf.begin(), BufferSize, MSG_WAITALL,
          reinterpret_cast<struct sockaddr *>(&clientAddr), &clientAddrLen);

      if (m_onReceivedCallback != nullptr) {
        m_onReceivedCallback(m_inBuf.begin(), m_inBuf.begin() + nBytes);
      }
    }
  }

private:
  using Container = std::array<std::byte, BufferSize>;
  int m_fd;
  struct sockaddr_in m_servAddr;
  Container m_inBuf;
  OnDataCallback *m_onReceivedCallback;
};

} // namespace Zen::Net

#endif // UDPSERVER_HPP
