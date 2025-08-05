#include <iostream>
#include <thread>
#include <chrono>

#include "cyphal/udp_frame.hpp"
#include "cyphal/udp_publisher.hpp"
#include "cyphal/udp_transport.hpp"
#include "ftl/native_udp_socket.hpp"
#include "ftl/native_ethernet_interface.hpp"

#include <uavcan/node/Heartbeat_1_0.hpp>

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
  
  // Create transport which handles socket creation and binding.
  cyphal::UdpTransport transport(lo);

  // Create the heartbeat publisher.
  cyphal::UdpPublisher<uavcan::node::Heartbeat_1_0> publisher(uavcan::node::Heartbeat_1_0::_traits_::FixedPortId,
    kSourceNodeId, transport);

  // Create a heartbeat message.
  uavcan::node::Heartbeat_1_0 msg{};
  msg.uptime = 0;
  msg.health.value = uavcan::node::Health_1_0::NOMINAL;
  msg.mode.value = uavcan::node::Mode_1_0::OPERATIONAL; 
  msg.vendor_specific_status_code = 0xAB;

  // Publish every 1s.
  while (1)
  {
    publisher.publish(msg);
    std::cout << "published health" << std::endl;
    
    std::this_thread::sleep_for(std::chrono::seconds(1));
    msg.uptime += 1;
  }
}
