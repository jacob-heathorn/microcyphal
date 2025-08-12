#include <iostream>
#include <thread>
#include <chrono>

#include "cyphal/udp_frame.hpp"
#include "cyphal/udp_publisher.hpp"
#include "cyphal/udp_transport.hpp"
#include "ftl/native_udp_socket.hpp"
#include "ftl/native_ethernet_interface.hpp"
#include "ftl/allocator/bump_allocator.hpp"
#include "ftl/allocator/bump_pool_buffer_strategy.hpp"

#include "uavcan/node/Heartbeat_1_0.hpp"

using namespace ftl::ipv4;

int main() {
    std::cout << "Cyphal/UDP Publisher Demo\n";
    std::cout << "==========================\n\n";

    // Create an allocator for the data frame
    static constexpr size_t POOL_MEMORY_SIZE = 16 * 1024;
    uint8_t* buffer = new uint8_t[POOL_MEMORY_SIZE];
    ftl::BumpAllocator allocator(buffer, POOL_MEMORY_SIZE);

    // Initialize Payload class with buffer strategy.
    std::array<std::size_t, 8> buffer_sizes = {32, 64, 128, 256, 512, 1024, 2048, 4096};
    ftl::allocator::BumpPoolBufferStrategy<8> buffer_strategy(allocator, buffer_sizes);
    ftl::ipv4::udp::Payload::initialize(buffer_strategy);

    // Setup interface on loopback interface.
    ftl::ethernet::NativeEthernetInterface lo{Address{"192.2.2.1"}, Mask{"255.255.255.0"}};
    
    // Create transport which handles socket creation and binding.
    cyphal::UdpTransport transport(lo);

    // Create the heartbeat publisher.
    const uint16_t subject_id = uavcan::node::Heartbeat_1_0::_traits_::FixedPortId;
    const uint16_t node_id = 42;  // Publisher node ID
    
    cyphal::UdpPublisher<uavcan::node::Heartbeat_1_0> publisher(
        subject_id,
        node_id,
        transport,
        4  // Priority
    );

    std::cout << "Publisher node ID: " << node_id << "\n";
    std::cout << "Publishing to subject ID: " << subject_id << " (0x" << std::hex << subject_id << std::dec << ")\n";
    std::cout << "Multicast address: 239.0." << (subject_id >> 8) << "." << (subject_id & 0xFF) << "\n";
    std::cout << "Port: " << cyphal::UdpTransport::kCyphalPort << "\n\n";
    std::cout << "Publishing heartbeat messages every second...\n";
    std::cout << "Press Ctrl+C to exit\n\n";

    // Heartbeat state
    uint32_t uptime = 0;
    std::uint8_t health_states[] = {
        uavcan::node::Health_1_0::NOMINAL,
        uavcan::node::Health_1_0::ADVISORY,
        uavcan::node::Health_1_0::CAUTION,
        uavcan::node::Health_1_0::WARNING
    };
    int health_index = 0;

    while (true) {
        // Create heartbeat message
        uavcan::node::Heartbeat_1_0 heartbeat;
        heartbeat.uptime = uptime++;
        heartbeat.health.value = health_states[health_index];
        heartbeat.mode.value = uavcan::node::Mode_1_0::OPERATIONAL;
        heartbeat.vendor_specific_status_code = 0x00;

        // Publish
        publisher.publish(heartbeat);

        // Display what we sent
        std::cout << "[" << std::chrono::system_clock::now().time_since_epoch().count() << "] "
                  << "Published: uptime=" << heartbeat.uptime 
                  << ", health=" << static_cast<int>(heartbeat.health.value)
                  << " (" << (heartbeat.health.value == uavcan::node::Health_1_0::NOMINAL ? "NOMINAL" :
                             heartbeat.health.value == uavcan::node::Health_1_0::ADVISORY ? "ADVISORY" :
                             heartbeat.health.value == uavcan::node::Health_1_0::CAUTION ? "CAUTION" :
                             "WARNING") << ")"
                  << ", mode=OPERATIONAL" << std::endl;

        // Cycle through health states every 4 heartbeats
        if (uptime % 4 == 0) {
            health_index = (health_index + 1) % 4;
        }

        // Wait 1 second
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    delete[] buffer;
    return 0;
}