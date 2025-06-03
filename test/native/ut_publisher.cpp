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

TEST_F(PublisherTest, PublisherWithReceiver) {
    // Create interface on loopback (same as hello_world)
    ftl::ethernet::NativeEthernetInterface interface(
        ftl::ipv4::Address("127.0.0.1"),
        ftl::ipv4::Mask("255.255.255.0")
    );
    
    // Use the same socket for both send and receive since NativeUdpSocket
    // is designed to handle multicast loopback with dual file descriptors
    auto socket = interface.CreateUdpSocket();
    ASSERT_TRUE(socket->open(4));
    ASSERT_TRUE(socket->bind(9382));
    
    // Join multicast group for heartbeat subject
    const uint16_t subject_id = uavcan::node::Heartbeat_1_0::_traits_::FixedPortId;
    const uint32_t multicast_addr = 0xEF000000u | uint32_t(subject_id);
    ASSERT_TRUE(socket->join_multicast_group(ftl::ipv4::Address(multicast_addr)));
    
    // Create a separate socket for publishing to avoid interference
    auto pub_socket = interface.CreateUdpSocket();
    ASSERT_TRUE(pub_socket->open(4));
    ASSERT_TRUE(pub_socket->bind(9384));  // Different port for publisher
    
    const uint16_t node_id = 42;
    cyphal::UdpPublisher<uavcan::node::Heartbeat_1_0> publisher(
        subject_id, std::move(pub_socket), node_id, 4
    );
    
    // Create and publish a heartbeat message (like hello_world)
    uavcan::node::Heartbeat_1_0 heartbeat;
    heartbeat.uptime = 12345;
    heartbeat.health.value = uavcan::node::Health_1_0::ADVISORY;
    heartbeat.mode.value = uavcan::node::Mode_1_0::MAINTENANCE;
    heartbeat.vendor_specific_status_code = 0xAB;
    
    // Publish the message
    publisher.publish(heartbeat);
    
    // Give time for multicast delivery on loopback interface
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
    
    // Receive the multicast message
    ftl::ipv4::Endpoint sender;
    auto payload = socket->receive(&sender);

    ASSERT_TRUE(payload);
    
    // Validate the received UDP datagram
    const size_t received_bytes = payload.size();
        
    std::cout << "Received " << received_bytes << " bytes from " 
                << sender.address().ToString().c_str() << ":" << sender.port() << std::endl;
    
    // Print raw bytes for debugging
    std::cout << "Raw UDP data: ";
    for (size_t i = 0; i < received_bytes; ++i) {
        printf("%02X ", payload.data()[i]);
        if ((i + 1) % 16 == 0) printf("\n               ");
    }
    std::cout << std::endl;
    
    // Validate Cyphal/UDP frame structure
    ASSERT_GE(received_bytes, cyphal::UdpFrame::kHeaderSize) << "Frame must be at least header size bytes";
    
    // Parse header fields according to UdpFrame layout
    const uint8_t* header = payload.data();
    
    // Version (low 4 bits of byte 0) and Priority (bits 7:5 of byte 1)
    const uint8_t version = header[0] & 0x0F;  // Low nibble
    const uint8_t priority = (header[1] >> 5) & 0x07;  // Bits 7:5
    EXPECT_EQ(version, 1u) << "Version should be 1";
    EXPECT_EQ(priority, 4u) << "Priority should be 4";
    
    // Source node ID (16 bits little-endian) - bytes 2-3
    const uint16_t src_node_id = header[2] | (uint16_t(header[3]) << 8);
    EXPECT_EQ(src_node_id, node_id) << "Source node ID should match";
    
    // Destination node ID (16 bits little-endian) - bytes 4-5
    const uint16_t dst_node_id = header[4] | (uint16_t(header[5]) << 8);
    EXPECT_EQ(dst_node_id, 0xFFFFu) << "Destination should be broadcast (0xFFFF)";
    
    // Data specifier (15 bits) and service flag (1 bit) - bytes 6-7
    const uint16_t data_spec_and_flag = header[6] | (uint16_t(header[7]) << 8);
    const uint16_t data_specifier = data_spec_and_flag & 0x7FFF;
    const bool service_flag = (data_spec_and_flag & 0x8000) != 0;
    EXPECT_EQ(data_specifier, subject_id) << "Data specifier should match subject ID";
    EXPECT_FALSE(service_flag) << "Service flag should be false for messages";
    
    // Transfer ID (64 bits little-endian) - bytes 8-15
    uint64_t transfer_id = 0;
    for (int i = 0; i < 8; ++i) {
        transfer_id |= (uint64_t(header[8 + i]) << (i * 8));
    }
    std::cout << "Transfer ID: " << transfer_id << std::endl;
    
    // Frame index and EOT flag (32 bits little-endian) - bytes 16-19
    uint32_t frame_and_eot = 0;
    for (int i = 0; i < 4; ++i) {
        frame_and_eot |= (uint32_t(header[16 + i]) << (i * 8));
    }
    const uint32_t frame_index = frame_and_eot & 0x7FFFFFFF;  // Bits 0:30
    const bool eot_flag = (frame_and_eot & 0x80000000) != 0;   // Bit 31
    EXPECT_EQ(frame_index, 0u) << "Frame index should be 0 for single-frame transfer";
    EXPECT_TRUE(eot_flag) << "End of transfer flag should be set";
    
    // User data (16 bits little-endian) - bytes 20-21
    const uint16_t user_data = header[20] | (uint16_t(header[21]) << 8);
    std::cout << "User data: 0x" << std::hex << user_data << std::dec << std::endl;
    
    // Header CRC (16 bits big-endian) - bytes 22-23
    const uint16_t received_header_crc = (uint16_t(header[22]) << 8) | header[23];
    const uint16_t computed_header_crc = etl::crc16_ccitt(header, header + cyphal::UdpFrame::kHeaderSize - cyphal::UdpFrame::kHeaderCrcSize);
    EXPECT_EQ(received_header_crc, computed_header_crc) << "Header CRC should be valid";
    
    std::cout << "Header CRC: received=0x" << std::hex << received_header_crc 
                << ", computed=0x" << computed_header_crc << std::dec << std::endl;
    
    // Payload and payload CRC
    if (received_bytes > cyphal::UdpFrame::kHeaderSize) {
        const size_t payload_size = received_bytes - cyphal::UdpFrame::kHeaderSize - cyphal::UdpFrame::kTransferCrcSize;
        const uint8_t* payload_data = header + cyphal::UdpFrame::kHeaderSize;
        const uint8_t* payload_crc_bytes = payload_data + payload_size;
        
        // Extract payload CRC (little-endian)
        uint32_t received_payload_crc = 0;
        for (size_t i = 0; i < cyphal::UdpFrame::kTransferCrcSize; ++i) {
            received_payload_crc |= (uint32_t(payload_crc_bytes[i]) << (i * 8));
        }
        
        const uint32_t computed_payload_crc = etl::crc32_c(payload_data, payload_data + payload_size);
        EXPECT_EQ(received_payload_crc, computed_payload_crc) << "Payload CRC should be valid";
        
        std::cout << "Payload CRC: received=0x" << std::hex << received_payload_crc 
                    << ", computed=0x" << computed_payload_crc << std::dec << std::endl;
        
        std::cout << "Payload (" << payload_size << " bytes): ";
        for (size_t i = 0; i < payload_size; ++i) {
            printf("%02X ", payload_data[i]);
        }
        std::cout << std::endl;
    }
    
    SUCCEED() << "Successfully validated Cyphal/UDP frame structure";
}
