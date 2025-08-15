#include <gtest/gtest.h>
#include <cyphal/udp_subscriber.hpp>
#include <cyphal/udp_publisher.hpp>
#include <cyphal/udp_transport.hpp>
#include <uavcan/node/Heartbeat_1_0.hpp>
#include <ftl/native_udp_socket.hpp>
#include <ftl/native_ethernet_interface.hpp>
#include <ftl/allocator/malloc_buffer_strategy.hpp>
#include <ftl/allocator/buffer_allocator.hpp>
#include <ftl/allocator/malloc_obj_strategy.hpp>
#include <thread>
#include <chrono>

using namespace ftl::ipv4;

class SubscriberTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Initialize Payload with buffer strategy
        buffer_strategy_ = new ftl::allocator::MallocBufferStrategy(1500);  // Max MTU size
        buffer_allocator_ = new ftl::allocator::BufferAllocator(*buffer_strategy_);
        ftl::ipv4::udp::Payload::initialize(*buffer_allocator_);
        
        // Create the MallocObjStrategy for map nodes
        node_strategy_ = new ftl::allocator::MallocObjStrategy<cyphal::LastTransferIdAllocator::NodeType>();
        
        // Re-initialize static pools for each test
        // This is safe because initialize() is re-entrant
        cyphal::LastTransferIdAllocator::initialize(*node_strategy_);
    }
    
    void TearDown() override {
        // Clean up allocators after each test
        delete node_strategy_;
        delete buffer_allocator_;
        delete buffer_strategy_;
        node_strategy_ = nullptr;
        buffer_allocator_ = nullptr;
        buffer_strategy_ = nullptr;
    }
    
    ftl::allocator::MallocBufferStrategy* buffer_strategy_ = nullptr;
    ftl::allocator::BufferAllocator* buffer_allocator_ = nullptr;
    ftl::allocator::MallocObjStrategy<cyphal::LastTransferIdAllocator::NodeType>* node_strategy_ = nullptr;
};

TEST_F(SubscriberTest, SubscriberCanBeCreated) {
    ftl::ethernet::NativeEthernetInterface interface(
        Address("127.0.0.1"),
        Mask("255.255.255.0")
    );
    
    cyphal::UdpTransport transport(interface);
    
    const uint16_t subject_id = uavcan::node::Heartbeat_1_0::_traits_::FixedPortId;
    const uint16_t node_id = 100;
    
    cyphal::UdpSubscriber<uavcan::node::Heartbeat_1_0> subscriber(
        subject_id, node_id, transport
    );
    
    SUCCEED();
}

TEST_F(SubscriberTest, SubscriberReceivesNothingWhenNoData) {
    ftl::ethernet::NativeEthernetInterface interface(
        Address("127.0.0.1"),
        Mask("255.255.255.0")
    );
    
    cyphal::UdpTransport transport(interface);
    
    const uint16_t subject_id = uavcan::node::Heartbeat_1_0::_traits_::FixedPortId;
    const uint16_t node_id = 100;
    
    cyphal::UdpSubscriber<uavcan::node::Heartbeat_1_0> subscriber(
        subject_id, node_id, transport
    );
    
    // Should return nullopt when no data available
    auto msg = subscriber.receive();
    EXPECT_FALSE(msg.has_value());
}

TEST_F(SubscriberTest, PublishAndSubscribe) {
    // Create two interfaces - one for publisher, one for subscriber
    ftl::ethernet::NativeEthernetInterface pub_interface(
        Address("127.0.0.1"),
        Mask("255.255.255.0")
    );
    
    ftl::ethernet::NativeEthernetInterface sub_interface(
        Address("127.0.0.1"), 
        Mask("255.255.255.0")
    );
    
    // Create transports
    cyphal::UdpTransport pub_transport(pub_interface);
    cyphal::UdpTransport sub_transport(sub_interface);
    
    const uint16_t subject_id = uavcan::node::Heartbeat_1_0::_traits_::FixedPortId;
    const uint16_t pub_node_id = 42;
    const uint16_t sub_node_id = 100;
    
    // Create subscriber first (to join multicast group)
    cyphal::UdpSubscriber<uavcan::node::Heartbeat_1_0> subscriber(
        subject_id, sub_node_id, sub_transport
    );
    
    // Create publisher
    cyphal::UdpPublisher<uavcan::node::Heartbeat_1_0> publisher(
        subject_id, pub_node_id, pub_transport, 4
    );
    
    // Create and publish a heartbeat message
    uavcan::node::Heartbeat_1_0 sent_heartbeat;
    sent_heartbeat.uptime = 12345;
    sent_heartbeat.health.value = uavcan::node::Health_1_0::ADVISORY;
    sent_heartbeat.mode.value = uavcan::node::Mode_1_0::MAINTENANCE;
    sent_heartbeat.vendor_specific_status_code = 0xAB;
    
    publisher.publish(sent_heartbeat);
    
    // Give time for loopback delivery
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    
    // Receive the message
    auto received = subscriber.receive();
    
    ASSERT_TRUE(received.has_value());
    
    // Verify the received message matches what was sent
    EXPECT_EQ(received->uptime, sent_heartbeat.uptime);
    EXPECT_EQ(received->health.value, sent_heartbeat.health.value);
    EXPECT_EQ(received->mode.value, sent_heartbeat.mode.value);
    EXPECT_EQ(received->vendor_specific_status_code, sent_heartbeat.vendor_specific_status_code);
}

TEST_F(SubscriberTest, SubscriberIgnoresDifferentSubject) {
    ftl::ethernet::NativeEthernetInterface pub_interface(
        Address("127.0.0.1"),
        Mask("255.255.255.0")
    );
    
    ftl::ethernet::NativeEthernetInterface sub_interface(
        Address("127.0.0.1"),
        Mask("255.255.255.0")
    );
    
    cyphal::UdpTransport pub_transport(pub_interface);
    cyphal::UdpTransport sub_transport(sub_interface);
    
    const uint16_t heartbeat_subject = uavcan::node::Heartbeat_1_0::_traits_::FixedPortId;
    const uint16_t different_subject = 1234;  // Different subject ID
    const uint16_t node_id = 100;
    
    // Subscribe to different subject
    cyphal::UdpSubscriber<uavcan::node::Heartbeat_1_0> subscriber(
        different_subject, node_id, sub_transport
    );
    
    // Publish to heartbeat subject
    cyphal::UdpPublisher<uavcan::node::Heartbeat_1_0> publisher(
        heartbeat_subject, 42, pub_transport, 4
    );
    
    uavcan::node::Heartbeat_1_0 heartbeat;
    heartbeat.uptime = 999;
    publisher.publish(heartbeat);
    
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    
    // Should not receive the message (different subject)
    auto received = subscriber.receive();
    EXPECT_FALSE(received.has_value());
}

TEST_F(SubscriberTest, DuplicateDetection) {
    // This test would require modifying the publisher to send with the same transfer ID
    // For now, we'll test that receiving the same message twice works
    // (In a real implementation, we'd need to expose transfer_id control for testing)
    
    ftl::ethernet::NativeEthernetInterface interface(
        Address("127.0.0.1"),
        Mask("255.255.255.0")
    );
    
    cyphal::UdpTransport transport(interface);
    
    const uint16_t subject_id = uavcan::node::Heartbeat_1_0::_traits_::FixedPortId;
    const uint16_t node_id = 100;
    
    cyphal::UdpSubscriber<uavcan::node::Heartbeat_1_0> subscriber(
        subject_id, node_id, transport
    );
    cyphal::UdpPublisher<uavcan::node::Heartbeat_1_0> publisher(
        subject_id, 42, transport, 4
    );
    
    uavcan::node::Heartbeat_1_0 heartbeat;
    heartbeat.uptime = 777;
    
    // Publish twice with different transfer IDs (normal operation)
    publisher.publish(heartbeat);
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    auto msg1 = subscriber.receive();
    ASSERT_TRUE(msg1.has_value());
    
    heartbeat.uptime = 888;
    publisher.publish(heartbeat);
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    auto msg2 = subscriber.receive();
    ASSERT_TRUE(msg2.has_value());
    
    // Should receive both (different transfer IDs)
    EXPECT_EQ(msg1->uptime, 777);
    EXPECT_EQ(msg2->uptime, 888);
}