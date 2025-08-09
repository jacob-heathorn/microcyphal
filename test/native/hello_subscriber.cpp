#include <iostream>
#include <thread>
#include <chrono>
#include <iomanip>

#include "cyphal/udp_frame.hpp"
#include "cyphal/udp_subscriber.hpp"
#include "cyphal/udp_transport.hpp"
#include "ftl/native_udp_socket.hpp"
#include "ftl/native_ethernet_interface.hpp"

#include "uavcan/node/Heartbeat_1_0.hpp"

using namespace ftl::ipv4;

int main() {
    std::cout << "Cyphal/UDP Subscriber Demo\n";
    std::cout << "===========================\n\n";

    // Create allocators for data frames and duplicate detection
    static constexpr size_t POOL_MEMORY_SIZE = 16 * 1024;
    static constexpr size_t DUP_DETECTION_SIZE = 4 * 1024;  // For duplicate detection map nodes
    uint8_t* buffer = new uint8_t[POOL_MEMORY_SIZE];
    uint8_t* dup_buffer = new uint8_t[DUP_DETECTION_SIZE];
    ftl::BumpAllocator allocator(buffer, POOL_MEMORY_SIZE);
    ftl::BumpAllocator dup_allocator(dup_buffer, DUP_DETECTION_SIZE);

    // Initialize data frame class with the memory allocator.
    ftl::DataFrame::initialize(allocator);
    
    // Create the BumpPoolAllocationStrategy for map nodes and initialize the shared pool
    ftl::BumpPoolAllocationStrategy<cyphal::LastTransferIdAllocationStrategy::NodeType> node_strategy(dup_allocator, 32);
    cyphal::LastTransferIdAllocationStrategy::initialize(node_strategy);

    // Setup interface on loopback interface.
    ftl::ethernet::NativeEthernetInterface lo{Address{"127.0.0.1"}, Mask{"255.255.255.0"}};
    
    // Create transport which handles socket creation and binding.
    cyphal::UdpTransport transport(lo);

    // Create the heartbeat subscriber.
    const uint16_t subject_id = uavcan::node::Heartbeat_1_0::_traits_::FixedPortId;
    const uint16_t node_id = 100;  // Subscriber node ID
    
    cyphal::UdpSubscriber<uavcan::node::Heartbeat_1_0> subscriber(
        subject_id,
        node_id,
        transport
    );

    std::cout << "Subscriber node ID: " << node_id << "\n";
    std::cout << "Subscribing to subject ID: " << subject_id << " (0x" << std::hex << subject_id << std::dec << ")\n";
    std::cout << "Multicast address: 239.0." << (subject_id >> 8) << "." << (subject_id & 0xFF) << "\n";
    std::cout << "Port: " << cyphal::UdpTransport::kCyphalPort << "\n\n";
    std::cout << "Waiting for heartbeat messages...\n";
    std::cout << "Press Ctrl+C to exit\n\n";

    // Statistics
    uint32_t messages_received = 0;

    while (true) {
        // Try to receive a message
        auto msg = subscriber.receive();
        
        if (msg.has_value()) {
            messages_received++;
            
            // Get current time
            auto now = std::chrono::system_clock::now();
            auto time_point = std::chrono::system_clock::to_time_t(now);
            
            // Display received message
            std::cout << "[" << std::put_time(std::localtime(&time_point), "%H:%M:%S") << "] "
                      << "Received #" << messages_received << ": ";
            
            std::cout << "uptime=" << msg->uptime << "s";
            
            std::cout << ", health=" << static_cast<int>(msg->health.value)
                      << " (" << (msg->health.value == uavcan::node::Health_1_0::NOMINAL ? "NOMINAL" :
                                 msg->health.value == uavcan::node::Health_1_0::ADVISORY ? "ADVISORY" :
                                 msg->health.value == uavcan::node::Health_1_0::CAUTION ? "CAUTION" :
                                 "WARNING") << ")";
            
            std::cout << ", mode=" << static_cast<int>(msg->mode.value)
                      << " (" << (msg->mode.value == uavcan::node::Mode_1_0::OPERATIONAL ? "OPERATIONAL" :
                                 msg->mode.value == uavcan::node::Mode_1_0::INITIALIZATION ? "INITIALIZATION" :
                                 msg->mode.value == uavcan::node::Mode_1_0::MAINTENANCE ? "MAINTENANCE" :
                                 "SOFTWARE_UPDATE") << ")";
            
            if (msg->vendor_specific_status_code != 0) {
                std::cout << ", vendor=0x" << std::hex << msg->vendor_specific_status_code << std::dec;
            }
            
            std::cout << std::endl;
        }
        
        // Small delay to avoid busy-waiting
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }

    delete[] buffer;
    return 0;
}