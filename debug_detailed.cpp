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

void print_buffer(const uint8_t* buf, size_t size) {
    for (size_t i = 0; i < size; i++) {
        std::cout << "0x" << std::hex << std::setfill('0') << std::setw(2) << (int)buf[i] << " ";
    }
    std::cout << std::dec;
}

int main() {
    std::cout << "=== Detailed Offset Tracking Debug ===" << std::endl;
    
    // Create test message
    Heartbeat_1_0 msg_orig;
    msg_orig.uptime = 0x12345678;
    msg_orig.health.value = Health_1_0::NOMINAL;  // 0
    msg_orig.mode.value = Mode_1_0::OPERATIONAL;  // 0  
    msg_orig.vendor_specific_status_code = 0xAB;

    // Test serialization
    constexpr size_t kBufSizeBytes = 7;
    uint8_t raw_buf[kBufSizeBytes];
    std::memset(raw_buf, 0, kBufSizeBytes);

    bitspan out_span(raw_buf, kBufSizeBytes);
    SerializeResult ser_ret = serialize(msg_orig, out_span);
    
    std::cout << "Serialized buffer: ";
    print_buffer(raw_buf, kBufSizeBytes);
    std::cout << " (" << ser_ret.value() << " bytes)" << std::endl;

    // Manual deserialization step by step to track offsets
    std::cout << "\n=== Manual Deserialization ===" << std::endl;
    
    const_bitspan in_span(raw_buf, kBufSizeBytes);
    std::cout << "Initial offset: " << in_span.offset() << " bits" << std::endl;
    
    // Read uptime
    uint32_t uptime = in_span.getU32(32U);
    std::cout << "Read uptime: 0x" << std::hex << uptime << std::dec << " from offset " << in_span.offset() << std::endl;
    in_span.add_offset(32U);
    std::cout << "After uptime, offset: " << in_span.offset() << " bits" << std::endl;
    
    // Align to byte boundary
    in_span.align_offset_to<8U>();
    std::cout << "After alignment, offset: " << in_span.offset() << " bits" << std::endl;
    
    // Read health
    std::cout << "Creating subspan for health at offset " << in_span.offset() << std::endl;
    auto health_subspan = in_span.subspan();
    std::cout << "Health subspan offset: " << health_subspan.offset() << " bits, size: " << health_subspan.size() << " bits" << std::endl;
    
    Health_1_0 health;
    auto health_result = deserialize(health, health_subspan);
    std::cout << "Health deserialize returned: " << health_result.value() << " bytes, health.value = " << (int)health.value << std::endl;
    
    // Advance main buffer
    in_span.add_offset(health_result.value() * 8U);
    std::cout << "After health, main offset: " << in_span.offset() << " bits" << std::endl;
    
    // Align again
    in_span.align_offset_to<8U>();
    std::cout << "After alignment, offset: " << in_span.offset() << " bits" << std::endl;
    
    // Read mode
    std::cout << "Creating subspan for mode at offset " << in_span.offset() << std::endl;
    auto mode_subspan = in_span.subspan();
    std::cout << "Mode subspan offset: " << mode_subspan.offset() << " bits, size: " << mode_subspan.size() << " bits" << std::endl;
    
    Mode_1_0 mode;
    auto mode_result = deserialize(mode, mode_subspan);
    std::cout << "Mode deserialize returned: " << mode_result.value() << " bytes, mode.value = " << (int)mode.value << std::endl;
    
    // Advance main buffer
    in_span.add_offset(mode_result.value() * 8U);
    std::cout << "After mode, main offset: " << in_span.offset() << " bits" << std::endl;
    
    // Read vendor code
    uint8_t vendor_code = in_span.getU8(8U);
    std::cout << "Read vendor_code: 0x" << std::hex << (int)vendor_code << std::dec << " from offset " << in_span.offset() << std::endl;
    in_span.add_offset(8U);
    std::cout << "Final offset: " << in_span.offset() << " bits" << std::endl;

    return 0;
}