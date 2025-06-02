#include <iostream>
#include <cstdint>
#include <cstring>
#include <iomanip>

// Include C++ headers with fixed paths
#include "firmware/include/cpp17/nunavut/support/serialization.hpp"
#include "firmware/include/cpp17/uavcan/node/Health_1_0.hpp"
#include "firmware/include/cpp17/uavcan/node/Mode_1_0.hpp"
#include "firmware/include/cpp17/uavcan/node/Heartbeat_1_0.hpp"

using namespace uavcan::node;
using nunavut::support::bitspan;
using nunavut::support::const_bitspan;
using nunavut::support::SerializeResult;

int main() {
    std::cout << "=== Fixed C++ Heartbeat Serialization Test ===" << std::endl;
    
    // Create test message
    Heartbeat_1_0 msg_orig;
    msg_orig.uptime = 0x12345678;
    msg_orig.health.value = Health_1_0::NOMINAL;  // 0
    msg_orig.mode.value = Mode_1_0::OPERATIONAL;  // 0  
    msg_orig.vendor_specific_status_code = 0xAB;

    std::cout << "Original message:" << std::endl;
    std::cout << "  uptime: 0x" << std::hex << msg_orig.uptime << " (" << std::dec << msg_orig.uptime << ")" << std::endl;
    std::cout << "  health: " << (int)msg_orig.health.value << std::endl;
    std::cout << "  mode: " << (int)msg_orig.mode.value << std::endl;  
    std::cout << "  vendor_code: 0x" << std::hex << (int)msg_orig.vendor_specific_status_code << std::dec << std::endl;

    // Test serialization
    constexpr size_t kBufSizeBytes = Heartbeat_1_0::_traits_::SerializationBufferSizeBytes;
    uint8_t raw_buf[kBufSizeBytes];
    std::memset(raw_buf, 0, kBufSizeBytes);

    bitspan out_span(raw_buf, kBufSizeBytes);
    SerializeResult ser_ret = serialize(msg_orig, out_span);
    
    std::cout << "\nSerialize result: " << ser_ret.value() << " bytes" << std::endl;
    
    // Print buffer contents
    std::cout << "Buffer contents: ";
    for (size_t i = 0; i < kBufSizeBytes; i++) {
        std::cout << "0x" << std::hex << std::setfill('0') << std::setw(2) << (int)raw_buf[i] << " ";
    }
    std::cout << std::dec << std::endl;

    // Test deserialization with FIXED constructor - use explicit pointer cast
    Heartbeat_1_0 msg_copy;
    const const_bitspan in_span(static_cast<const uint8_t*>(raw_buf), kBufSizeBytes);
    SerializeResult deser_ret = deserialize(msg_copy, in_span);
    
    std::cout << "\nDeserialize result: " << deser_ret.value() << " bytes" << std::endl;
    
    std::cout << "Deserialized message:" << std::endl;
    std::cout << "  uptime: 0x" << std::hex << msg_copy.uptime << " (" << std::dec << msg_copy.uptime << ")" << std::endl;
    std::cout << "  health: " << (int)msg_copy.health.value << std::endl;
    std::cout << "  mode: " << (int)msg_copy.mode.value << std::endl;
    std::cout << "  vendor_code: 0x" << std::hex << (int)msg_copy.vendor_specific_status_code << std::dec << std::endl;

    // Check for mismatches
    bool all_match = true;
    if (msg_copy.uptime != msg_orig.uptime) {
        std::cout << "\n❌ uptime mismatch!" << std::endl;
        all_match = false;
    }
    if (msg_copy.health.value != msg_orig.health.value) {
        std::cout << "❌ health mismatch!" << std::endl;
        all_match = false;
    }
    if (msg_copy.mode.value != msg_orig.mode.value) {
        std::cout << "❌ mode mismatch!" << std::endl;
        all_match = false;
    }
    if (msg_copy.vendor_specific_status_code != msg_orig.vendor_specific_status_code) {
        std::cout << "❌ vendor_code mismatch!" << std::endl;
        all_match = false;
    }
    
    if (all_match) {
        std::cout << "\n✅ All fields match! Serialization/Deserialization works correctly!" << std::endl;
    }

    return 0;
}