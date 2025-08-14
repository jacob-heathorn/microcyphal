#include <iostream>
#include <thread>
#include <chrono>
#include <iomanip>

#include "cyphal/udp_frame.hpp"
#include "cyphal/udp_subscriber.hpp"
#include "cyphal/udp_transport.hpp"
#include "ftl/native_udp_socket.hpp"
#include "ftl/native_ethernet_interface.hpp"
#include "ftl/allocator/malloc_buffer_strategy.hpp"
#include "ftl/allocator/buffer_allocator.hpp"
#include "ftl/allocator/malloc_strategy.hpp"

#include "uavcan/node/Heartbeat_1_0.hpp"

using namespace ftl::ipv4;

int main() {
    std::cout << "Cyphal/UDP Subscriber Demo\n";
    std::cout << "===========================\n\n";

    // Initialize Payload class with buffer strategy.
    ftl::allocator::MallocBufferStrategy buffer_strategy(1500);  // Max MTU size
    ftl::allocator::BufferAllocator buffer_allocator(buffer_strategy);
    ftl::ipv4::udp::Payload::initialize(buffer_allocator);
    
    // Create the MallocObjStrategy for map nodes and initialize the shared pool
    ftl::allocator::MallocObjStrategy<cyphal::LastTransferIdAllocator::NodeType> node_strategy;
    cyphal::LastTransferIdAllocator::initialize(node_strategy);

    // Setup interface to listen on the embedded network.
    ftl::ethernet::NativeEthernetInterface lo{Address{"192.2.2.1"}, Mask{"255.255.255.0"}};
    
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
                std::cout << ", vendor=0x" << std::hex << static_cast<unsigned int>(msg->vendor_specific_status_code) << std::dec;
            }
            
            std::cout << std::endl;
        }
        
        // Small delay to avoid busy-waiting
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }

    return 0;
}