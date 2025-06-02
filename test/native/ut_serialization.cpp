#include <gtest/gtest.h>

#include <cstring>

#include "uavcan/node/Heartbeat_1_0.hpp"


using namespace uavcan::node;
using nunavut::support::bitspan;
using nunavut::support::const_bitspan;
using nunavut::support::SerializeResult;

TEST(HeartbeatRoundTripTest, SerializeDeserialize) {
  // KNOWN ISSUE: This test currently FAILS due to nunavut code generation bugs
  //
  // The generated serialize/deserialize functions have offset tracking bugs:
  // 1. serialize() returns wrong byte count (1 instead of 7) but data layout is correct
  // 2. deserialize() has offset tracking bugs and reads from wrong positions
  //
  // Evidence of bugs:
  // - serialize() writes correct data to buffer: 0x78 0x56 0x34 0x12 0x00 0x00 0xAB
  // - But deserialize() reads wrong values, e.g.:
  //   * uptime: reads 2386092 instead of 305419896 (0x12345678)
  //   * mode: reads 3 instead of 0 (OPERATIONAL)
  //   * vendor_code: reads 0 instead of 0xAB
  //
  // The issue appears to be in how subspan offsets are tracked in nested serialization
  // calls within the generated code. The main bitspan offset isn't properly advanced
  // when serializing/deserializing nested objects (Health, Mode).
  //
  // This test documents the expected behavior and will pass once nunavut is fixed.
  // For now, the microcyphal publisher works correctly because it only uses serialize(),
  // which produces the correct Cyphal message format despite returning wrong byte counts.
  
  Heartbeat_1_0 msg_orig;
  msg_orig.uptime                     = 0x12345678;  // Should be 0x78 0x56 0x34 0x12 (little-endian)
  msg_orig.health.value               = Health_1_0::NOMINAL;     // Should be 0x00
  msg_orig.mode.value                 = Mode_1_0::OPERATIONAL;   // Should be 0x00  
  msg_orig.vendor_specific_status_code = 0xAB;                    // Should be 0xAB

  constexpr size_t kBufSizeBytes = Heartbeat_1_0::_traits_::SerializationBufferSizeBytes;
  uint8_t raw_buf[kBufSizeBytes];
  std::memset(raw_buf, 0, kBufSizeBytes);

  // Serialize - this works correctly and produces proper Cyphal message format
  bitspan out_span(raw_buf, kBufSizeBytes);
  SerializeResult ser_ret = serialize(msg_orig, out_span);
  ASSERT_GE(ser_ret, 0) << "Serialization failed";
  // NOTE: ser_ret returns 1 instead of 7 due to offset bug, but data is correct

  // Deserialize - this has offset bugs and reads from wrong positions
  Heartbeat_1_0 msg_copy;
  const const_bitspan in_span(raw_buf, kBufSizeBytes);
  SerializeResult deser_ret = deserialize(msg_copy, in_span);
  ASSERT_GE(deser_ret, 0) << "Deserialization failed";
  // NOTE: deser_ret returns 1 instead of 7 due to offset bug, and data is wrong

  // These comparisons FAIL due to nunavut deserialize offset bugs:
  EXPECT_EQ(msg_copy.uptime, msg_orig.uptime);                          // FAILS: gets wrong value
  EXPECT_EQ(msg_copy.health.value, msg_orig.health.value);              // Passes: both 0
  EXPECT_EQ(msg_copy.mode.value, msg_orig.mode.value);                  // FAILS: gets wrong value  
  EXPECT_EQ(msg_copy.vendor_specific_status_code, msg_orig.vendor_specific_status_code);  // FAILS: gets wrong value
}
