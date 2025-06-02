#include <gtest/gtest.h>

#include <cstring>

#include "uavcan/node/Heartbeat_1_0.hpp"

using namespace uavcan::node;
using nunavut::support::bitspan;
using nunavut::support::const_bitspan;
using nunavut::support::SerializeResult;

TEST(HeartbeatRoundTripTest, SerializeDeserialize) {
  // FIXED: This test now works correctly with the nunavut C++ constructor ambiguity fix
  //
  // The issue was a constructor ambiguity in const_bitspan:
  // - const_bitspan(array, size) was calling the wrong constructor
  // - It interpreted 'size' as 'offset_bits' instead of buffer size
  // - This caused data corruption during deserialization
  //
  // Solution: Use explicit cast to force pointer constructor:
  // - const_bitspan(static_cast<const uint8_t*>(raw_buf), kBufSizeBytes)
  //
  // Both serialization and deserialization now work correctly and return proper byte counts.
  
  Heartbeat_1_0 msg_orig;
  msg_orig.uptime                     = 0x12345678;  // Should be 0x78 0x56 0x34 0x12 (little-endian)
  msg_orig.health.value               = Health_1_0::NOMINAL;     // Should be 0x00
  msg_orig.mode.value                 = Mode_1_0::OPERATIONAL;   // Should be 0x00  
  msg_orig.vendor_specific_status_code = 0xAB;                    // Should be 0xAB

  constexpr size_t kBufSizeBytes = Heartbeat_1_0::_traits_::SerializationBufferSizeBytes;
  uint8_t raw_buf[kBufSizeBytes];
  std::memset(raw_buf, 0, kBufSizeBytes);

  // Serialize - explicitly use pointer constructor to avoid ambiguity
  bitspan out_span(static_cast<uint8_t*>(raw_buf), kBufSizeBytes);
  SerializeResult ser_ret = serialize(msg_orig, out_span);
  ASSERT_GE(ser_ret, 0) << "Serialization failed";
  EXPECT_EQ(static_cast<size_t>(ser_ret.value()), kBufSizeBytes) << "Serialization should return 7 bytes";

  // Deserialize - explicitly use pointer constructor to avoid ambiguity
  Heartbeat_1_0 msg_copy;
  const const_bitspan in_span(static_cast<const uint8_t*>(raw_buf), kBufSizeBytes);
  SerializeResult deser_ret = deserialize(msg_copy, in_span);
  ASSERT_GE(deser_ret, 0) << "Deserialization failed";
  EXPECT_EQ(static_cast<size_t>(deser_ret.value()), kBufSizeBytes) << "Deserialization should return 7 bytes";

  // Verify data integrity - all fields should match exactly:
  EXPECT_EQ(msg_copy.uptime, msg_orig.uptime);
  EXPECT_EQ(msg_copy.health.value, msg_orig.health.value);
  EXPECT_EQ(msg_copy.mode.value, msg_orig.mode.value);
  EXPECT_EQ(msg_copy.vendor_specific_status_code, msg_orig.vendor_specific_status_code);
}
