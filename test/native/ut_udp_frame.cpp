#include <gtest/gtest.h>

#include "cyphal/udp_frame.hpp"
#include "ftl/allocator/malloc_buffer_strategy.hpp"
#include "ftl/allocator/buffer_allocator.hpp"


class UdpFrameTest : public ::testing::Test {
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

TEST_F(UdpFrameTest, ConstructorSetsVersion) {
    cyphal::UdpFrame f(0);
    EXPECT_EQ(f.version(), cyphal::UdpFrame::kHeaderVersion);
}

TEST_F(UdpFrameTest, VersionAndPriority) {
    cyphal::UdpFrame f(0);
    f.set_version(7);
    EXPECT_EQ(f.version(), 7);
    f.set_priority(5);
    EXPECT_EQ(f.priority(), 5);
    // ensure setting priority didn’t clobber version
    EXPECT_EQ(f.version(), 7);
}

TEST_F(UdpFrameTest, SourceAndDestinationNodeId) {
    cyphal::UdpFrame f(0);
    f.set_source_node_id(0x1234);
    EXPECT_EQ(f.source_node_id(), 0x1234);
    f.set_destination_node_id(0xABCD);
    EXPECT_EQ(f.destination_node_id(), 0xABCD);
}

TEST_F(UdpFrameTest, DataSpecifierAndServiceFlag) {
    cyphal::UdpFrame f(0);
    // 15-bit range
    f.set_data_specifier(0x5AAA);
    EXPECT_EQ(f.data_specifier(), 0x5AAA);
    // service/message bit
    f.set_service_not_message(true);
    EXPECT_TRUE(f.service_not_message());
    f.set_service_not_message(false);
    EXPECT_FALSE(f.service_not_message());
}

TEST_F(UdpFrameTest, TransferIdAndFrameIndexAndEot) {
    cyphal::UdpFrame f(0);
    uint64_t tid = 0x1122334455667788ULL;
    f.set_transfer_id(tid);
    EXPECT_EQ(f.transfer_id(), tid);

    uint32_t idx = 0x0F0F0F0F;
    f.set_frame_index(idx);
    EXPECT_EQ(f.frame_index(), idx);
    f.set_end_of_transfer(true);
    EXPECT_TRUE(f.end_of_transfer());
    f.set_end_of_transfer(false);
    EXPECT_FALSE(f.end_of_transfer());
}

TEST_F(UdpFrameTest, UserDataAndCrc) {
    cyphal::UdpFrame f(0);
    f.set_user_data(0xCAFE);
    EXPECT_EQ(f.user_data(), 0xCAFE);

    f.set_header_crc16(0xBEEF);
    EXPECT_EQ(f.header_crc16(), 0xBEEF);
}
