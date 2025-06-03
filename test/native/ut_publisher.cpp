#include <gtest/gtest.h>
#include <cyphal/publisher.hpp>
#include <uavcan/node/Heartbeat_1_0.hpp>
#include <ftl/native_udp_socket.hpp>
#include <ftl/native_ethernet_interface.hpp>
#include <ftl/bump_allocator.hpp>
#include <ftl/data_frame.hpp>
#include <cyphal/udp_frame.hpp>
#include <array>
#include <thread>
#include <chrono>
#include <cstring>
#include <arpa/inet.h>

/*
 * Publisher Unit Tests
 * 
 * NOTE: These tests validate the publisher can be created and can send messages
 * without crashing, but they don't verify the actual UDP datagram content over
 * the network since we don't have a subscriber implementation yet.
 * 
 * For end-to-end validation of the Cyphal/UDP frame format:
 * 1. Run the hello-world example: `rip -r native-debug:hello-world`
 * 2. Monitor with yakut in another terminal:
 *    `yakut mon`
 *    or
 *    `yakut sub uavcan.node.Heartbeat.1.0`
 * 
 * This will show that the publisher correctly sends Cyphal/UDP frames with:
 * - Subject ID 7509 (heartbeat)
 * - Proper multicast addressing (239.0.29.85:9382)
 * - Valid CRC checksums
 * - Correct header format according to the Cyphal specification
 * 
 * TODO: Implement a Cyphal subscriber to enable automated end-to-end testing
 *       of the publisher datagram format validation.
 */

class PublisherTest : public ::testing::Test {
protected:
    static constexpr size_t POOL_MEMORY_SIZE = 16 * 1024;
    uint8_t* buffer_;
    ftl::BumpAllocator* allocator_;

    void SetUp() override {
        buffer_ = new uint8_t[POOL_MEMORY_SIZE];
        allocator_ = new ftl::BumpAllocator(buffer_, POOL_MEMORY_SIZE);
        ftl::DataFrame::initialize(*allocator_);
    }

    void TearDown() override {
        delete allocator_;
        delete[] buffer_;
    }
};

TEST_F(PublisherTest, PublisherCanBeCreated) {
    // Create interface
    ftl::ethernet::NativeEthernetInterface interface(
        ftl::ipv4::Address(127, 0, 0, 1),
        ftl::ipv4::Mask(255, 0, 0, 0)
    );
    
    // Create socket for publisher
    auto socket = interface.CreateUdpSocket();
    ASSERT_TRUE(socket->open());
    
    // Create publisher
    const uint16_t subject_id = 7509;  // Heartbeat subject ID
    const uint16_t node_id = 42;
    
    cyphal::UdpPublisher<uavcan::node::Heartbeat_1_0> publisher(
        subject_id, std::move(socket), node_id, 4  // priority 4 = nominal
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
    
    // Create socket for publisher
    auto socket = interface.CreateUdpSocket();
    ASSERT_TRUE(socket->open());
    
    // Create publisher
    const uint16_t subject_id = 7509;
    const uint16_t node_id = 42;
    
    cyphal::UdpPublisher<uavcan::node::Heartbeat_1_0> publisher(
        subject_id, std::move(socket), node_id, 4
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

TEST_F(PublisherTest, UdpFrameHeaderLayout) {
    // Test that the UdpFrame creates the correct header layout
    // Create a frame with some buffer space
    cyphal::UdpFrame frame(256);
    
    // Set some values
    frame.set_version(1);
    frame.set_priority(4);
    frame.set_source_node_id(42);
    frame.set_destination_node_id(0xFFFF);
    frame.set_data_specifier(7509);
    frame.set_service_not_message(false);
    frame.set_transfer_id(12345);
    frame.set_frame_index(0);
    frame.set_end_of_transfer(true);
    
    // Check version
    EXPECT_EQ(frame.version(), 1u) << "Version should be 1";
    
    // Check priority
    EXPECT_EQ(frame.priority(), 4u) << "Priority should be 4";
    
    // Check source node ID
    EXPECT_EQ(frame.source_node_id(), 42u);
    
    // Check destination node ID
    EXPECT_EQ(frame.destination_node_id(), 0xFFFFu);
    
    // Check data specifier
    EXPECT_EQ(frame.data_specifier(), 7509u) << "Data specifier should be 7509";
    EXPECT_FALSE(frame.service_not_message()) << "Service flag should be false (message)";
    
    // Check transfer ID
    EXPECT_EQ(frame.transfer_id(), 12345u);
    
    // Check frame index and EOT
    EXPECT_EQ(frame.frame_index(), 0u) << "Frame index should be 0";
    EXPECT_TRUE(frame.end_of_transfer()) << "EOT flag should be set";
}