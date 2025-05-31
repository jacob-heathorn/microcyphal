#include <iostream>
#include <thread>
#include <chrono>

#include "cyphal/udp_frame.hpp"
#include "cyphal/publisher.hpp"
#include "ftl/native_udp_socket.hpp"
#include "ftl/native_ethernet_interface.hpp"

#include <uavcan/node/Health_1_0.hpp>

// The port number is defined in the Cyphal/UDP Specification.
static constexpr uint16_t kCyphalUdpPort = 9382U;

static constexpr uint16_t kSourceNodeId = 1001;
static constexpr uint16_t kSubjectId = 2001;

int main() {
  using namespace ftl::ipv4;

  std::cout << "Hello World!" << std::endl;

  // Create an allocator for the data frame
  static constexpr size_t POOL_MEMORY_SIZE = 16 * 1024;
  uint8_t* buffer = new uint8_t[POOL_MEMORY_SIZE];
  ftl::BumpAllocator allocator(buffer, POOL_MEMORY_SIZE);

  // Initialize data frame class with the memory allocator.
  ftl::DataFrame::initialize(allocator);

  cyphal::UdpFrame f(2);

  std::cout << "version: " << (uint32_t)f.version() << std::endl;

  // Setup interface on loopback interface.
  ftl::ethernet::NativeEthernetInterface lo{Address{"127.0.0.1"}, Mask{"255.255.255.0"}};
  auto socket = lo.CreateUdpSocket();
  if (!socket->open(4)) {
    std::cerr << "Failed to open\n";
    return 1;
  }
  
  if (!socket->bind(kCyphalUdpPort)) {
    std::cerr << "Failed to bind\n";
    return 1;
  }

  cyphal::UdpPublisher<uavcan::node::Health_1_0> publisher(kSubjectId, std::move(socket), kSourceNodeId);

  uavcan::node::Health_1_0 msg{};
  msg.value = 17;

  while (1)
  {
    publisher.publish(msg);
    
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
  }
}
