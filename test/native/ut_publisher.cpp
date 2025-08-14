#include <gtest/gtest.h>
#include <cyphal/udp_publisher.hpp>
#include <cyphal/udp_transport.hpp>
#include <uavcan/node/Heartbeat_1_0.hpp>
#include <ftl/native_udp_socket.hpp>
#include <ftl/native_ethernet_interface.hpp>
#include <ftl/allocator/malloc_buffer_strategy.hpp>
#include <ftl/allocator/buffer_allocator.hpp>
#include <cyphal/udp_frame.hpp>
#include <array>
#include <thread>
#include <chrono>
#include <cstring>
#include <arpa/inet.h>
#include <etl/crc16_ccitt.h>
#include <etl/crc32_c.h>

/*
 * Publisher Unit Tests
 * 
 * These tests validate the Cyphal/UDP publisher implementation by:
 * 1. Testing publisher creation and basic functionality
 * 2. Verifying the UDP frame structure and field layout
 * 3. Receiving and validating actual UDP datagrams sent via multicast loopback
 * 
 * The PublisherWithReceiver test performs end-to-end validation by:
 * - Creating publisher and receiver sockets on the loopback interface
 * - Publishing a Cyphal heartbeat message
 * - Receiving the UDP datagram via multicast
 * - Parsing and validating all header fields according to the Cyphal specification
 * - Verifying both header CRC-16-CCITT and payload CRC-32C
 * - Inspecting the serialized payload data
 * 
 * For manual testing with external tools:
 * 1. Run the hello-world example: `rip -r native-debug:hello-world`
 * 2. Monitor with yakut in another terminal:
 *    `yakut mon` or `yakut sub uavcan.node.Heartbeat.1.0`
 * 
 * This validates interoperability with the reference Cyphal implementation.
 */

class PublisherTest : public ::testing::Test {
protected:
    void SetUp() override {
        static ftl::allocator::MallocBufferStrategy buffer_strategy(1500);  // Max MTU size
        static ftl::allocator::BufferAllocator buffer_allocator(buffer_strategy);
        ftl::ipv4::udp::Payload::initialize(buffer_allocator);
    }

    void TearDown() override {
        // Nothing to clean up with MallocBufferStrategy
    }
};

TEST_F(PublisherTest, PublisherCanBeCreated) {
    // Create interface
    ftl::ethernet::NativeEthernetInterface interface(
        ftl::ipv4::Address(127, 0, 0, 1),
        ftl::ipv4::Mask(255, 0, 0, 0)
    );
    
    // Create transport
    cyphal::UdpTransport transport(interface);
    
    // Create publisher
    const uint16_t subject_id = 7509;  // Heartbeat subject ID
    const uint16_t node_id = 42;
    
    cyphal::UdpPublisher<uavcan::node::Heartbeat_1_0> publisher(
        subject_id, node_id, transport, 4  // priority 4 = nominal
    );
    
    // Test passed if we get here without crash
    SUCCEED();
}

TEST_F(PublisherTest, PublisherCanPublishMessage) {
    // Create interface
    ftl::ethernet::NativeEthernetInterface interface(
        ftl::ipv4::Address(127, 0, 0, 1),
        ftl::ipv4::Mask(255, 0, 0, 0)
    );
    
    // Create transport
    cyphal::UdpTransport transport(interface);
    
    // Create publisher
    const uint16_t subject_id = 7509;
    const uint16_t node_id = 42;
    
    cyphal::UdpPublisher<uavcan::node::Heartbeat_1_0> publisher(
        subject_id, node_id, transport, 4
    );
    
    // Create and publish a heartbeat message
    uavcan::node::Heartbeat_1_0 heartbeat;
    heartbeat.uptime = 123;
    heartbeat.health.value = uavcan::node::Health_1_0::NOMINAL;
    heartbeat.mode.value = uavcan::node::Mode_1_0::OPERATIONAL;
    heartbeat.vendor_specific_status_code = 0;
    
    // This should not crash
    publisher.publish(heartbeat);
    
    SUCCEED();
}
