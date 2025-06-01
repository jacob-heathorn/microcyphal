#include <gtest/gtest.h>

#include <cstring>

#include "uavcan/node/Heartbeat_1_0.hpp"


using namespace uavcan::node;
using nunavut::support::bitspan;
using nunavut::support::const_bitspan;
using nunavut::support::SerializeResult;

TEST(HeartbeatRoundTripTest, SerializeDeserialize) {
  // 1) Construct a Heartbeat_1_0 and assign nonzero values to every field:
  Heartbeat_1_0 msg_orig;
  msg_orig.uptime                     = 0x12345678;            // 305419896
  msg_orig.health.value               = Health_1_0::NOMINAL;   // valid enumerator
  msg_orig.mode.value                 = Mode_1_0::OPERATIONAL; // valid enumerator
  msg_orig.vendor_specific_status_code = 0xAB;                  // nonzero vendor code

  // 2) Prepare a buffer of exactly SerializationBufferSizeBytes (7 bytes) and zero it:
  constexpr size_t kBufSizeBytes = Heartbeat_1_0::_traits_::SerializationBufferSizeBytes;
  uint8_t raw_buf[kBufSizeBytes];
  std::memset(raw_buf, 0, kBufSizeBytes);

  // 3) Serialize into a bitspan of length = kBufSizeBytes * 8 bits
  bitspan out_span(raw_buf, static_cast<size_t>(kBufSizeBytes * 8));
  SerializeResult ser_ret = serialize(msg_orig, out_span);
  ASSERT_GE(ser_ret, 0) << "Serialization failed with code " << ser_ret;
  size_t ser_bytes = static_cast<size_t>(ser_ret);
  EXPECT_EQ(ser_bytes, kBufSizeBytes);

  // 4) Now deserialize from the same buffer
  Heartbeat_1_0 msg_copy;
  const const_bitspan in_span(raw_buf, static_cast<size_t>(ser_bytes * 8));
  SerializeResult deser_ret = deserialize(msg_copy, in_span);
  ASSERT_GE(deser_ret, 0) << "Deserialization failed with code " << deser_ret;
  size_t deser_bytes = static_cast<size_t>(deser_ret);
  EXPECT_EQ(deser_bytes, kBufSizeBytes);

  // 5) Verify every field matches
  EXPECT_EQ(msg_copy.uptime, msg_orig.uptime);
  EXPECT_EQ(msg_copy.health.value, msg_orig.health.value);
  EXPECT_EQ(msg_copy.mode.value, msg_orig.mode.value);
  EXPECT_EQ(
      msg_copy.vendor_specific_status_code,
      msg_orig.vendor_specific_status_code
  );
}
