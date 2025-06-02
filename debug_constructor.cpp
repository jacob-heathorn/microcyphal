#include <iostream>
#include <cstdint>
#include <cstring>

// Include C++ headers with fixed paths
#include "firmware/include/cpp17/nunavut/support/serialization.hpp"

using nunavut::support::const_bitspan;

int main() {
    constexpr size_t kBufSizeBytes = 7;
    uint8_t raw_buf[kBufSizeBytes] = {0x78, 0x56, 0x34, 0x12, 0x00, 0x00, 0xab};

    std::cout << "=== Constructor Disambiguation Test ===" << std::endl;

    // Test 1: Array parameter (might be ambiguous)
    std::cout << "Test 1 - Array parameter:" << std::endl;
    const_bitspan span1(raw_buf, kBufSizeBytes);
    std::cout << "  offset: " << span1.offset() << " bits" << std::endl;

    // Test 2: Explicit pointer cast  
    std::cout << "Test 2 - Explicit pointer cast:" << std::endl;
    const_bitspan span2(static_cast<const uint8_t*>(raw_buf), kBufSizeBytes);
    std::cout << "  offset: " << span2.offset() << " bits" << std::endl;

    // Test 3: Array reference (explicit array constructor)
    std::cout << "Test 3 - Array reference:" << std::endl;
    const_bitspan span3(raw_buf);  // Should use array constructor
    std::cout << "  offset: " << span3.offset() << " bits" << std::endl;

    // Test 4: Explicit offset parameter
    std::cout << "Test 4 - Explicit offset 0:" << std::endl;
    const_bitspan span4(raw_buf, kBufSizeBytes, 0);
    std::cout << "  offset: " << span4.offset() << " bits" << std::endl;

    // Test 5: Non-zero explicit offset
    std::cout << "Test 5 - Explicit offset 3:" << std::endl;
    const_bitspan span5(raw_buf, kBufSizeBytes, 3);
    std::cout << "  offset: " << span5.offset() << " bits" << std::endl;

    return 0;
}