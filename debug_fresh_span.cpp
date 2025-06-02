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
    std::cout << "=== Testing Fresh Bitspan Issue ===" << std::endl;
    
    // Create test message
    Heartbeat_1_0 msg_orig;
    msg_orig.uptime = 0x12345678;
    msg_orig.health.value = Health_1_0::NOMINAL;  // 0
    msg_orig.mode.value = Mode_1_0::OPERATIONAL;  // 0  
    msg_orig.vendor_specific_status_code = 0xAB;

    // Test serialization with separate buffer
    constexpr size_t kBufSizeBytes = 7;
    uint8_t raw_buf[kBufSizeBytes];
    std::memset(raw_buf, 0, kBufSizeBytes);

    // Use a completely separate bitspan for serialization
    {
        bitspan out_span(raw_buf, kBufSizeBytes);
        std::cout << "Serialization out_span initial offset: " << out_span.offset() << " bits" << std::endl;
        SerializeResult ser_ret = serialize(msg_orig, out_span);
        std::cout << "Serialization returned: " << ser_ret.value() << " bytes" << std::endl;
        std::cout << "Serialization out_span final offset: " << out_span.offset() << " bits" << std::endl;
    }
    
    // Print buffer
    std::cout << "Buffer: ";
    for (size_t i = 0; i < kBufSizeBytes; i++) {
        std::cout << "0x" << std::hex << std::setfill('0') << std::setw(2) << (int)raw_buf[i] << " ";
    }
    std::cout << std::dec << std::endl;

    // Use a completely fresh bitspan for deserialization
    std::cout << "\n=== Fresh Deserialization ===" << std::endl;
    {
        const_bitspan in_span(raw_buf, kBufSizeBytes);
        std::cout << "Deserialization in_span initial offset: " << in_span.offset() << " bits" << std::endl;
        
        Heartbeat_1_0 msg_copy;
        SerializeResult deser_ret = deserialize(msg_copy, in_span);
        
        std::cout << "Deserialization returned: " << deser_ret.value() << " bytes" << std::endl;
        std::cout << "Deserialization in_span final offset: " << in_span.offset() << " bits" << std::endl;
        
        std::cout << "uptime: 0x" << std::hex << msg_copy.uptime << std::dec << std::endl;
        std::cout << "health: " << (int)msg_copy.health.value << std::endl;
        std::cout << "mode: " << (int)msg_copy.mode.value << std::endl;
        std::cout << "vendor_code: 0x" << std::hex << (int)msg_copy.vendor_specific_status_code << std::dec << std::endl;
    }

    // Test with explicit offset 0
    std::cout << "\n=== Explicit Offset 0 ===" << std::endl;
    {
        const_bitspan in_span(raw_buf, kBufSizeBytes, 0);  // Explicitly set offset to 0
        std::cout << "Explicit in_span initial offset: " << in_span.offset() << " bits" << std::endl;
        
        Heartbeat_1_0 msg_copy2;
        SerializeResult deser_ret2 = deserialize(msg_copy2, in_span);
        
        std::cout << "uptime: 0x" << std::hex << msg_copy2.uptime << std::dec << std::endl;
        std::cout << "health: " << (int)msg_copy2.health.value << std::endl;
        std::cout << "mode: " << (int)msg_copy2.mode.value << std::endl;
        std::cout << "vendor_code: 0x" << std::hex << (int)msg_copy2.vendor_specific_status_code << std::dec << std::endl;
    }

    return 0;
}