#pragma once

#include <cstdint>

namespace cyphal {

// Inline functions for efficient byte serialization with explicit endianness

// Write uint16_t in little-endian format
inline void writeU16LE(uint8_t* dest, uint16_t value) {
    dest[0] = static_cast<uint8_t>(value & 0xFF);
    dest[1] = static_cast<uint8_t>((value >> 8) & 0xFF);
}

// Write uint16_t in big-endian format
inline void writeU16BE(uint8_t* dest, uint16_t value) {
    dest[0] = static_cast<uint8_t>((value >> 8) & 0xFF);
    dest[1] = static_cast<uint8_t>(value & 0xFF);
}

// Write uint32_t in little-endian format
inline void writeU32LE(uint8_t* dest, uint32_t value) {
    dest[0] = static_cast<uint8_t>(value & 0xFF);
    dest[1] = static_cast<uint8_t>((value >> 8) & 0xFF);
    dest[2] = static_cast<uint8_t>((value >> 16) & 0xFF);
    dest[3] = static_cast<uint8_t>((value >> 24) & 0xFF);
}

// Write uint32_t in big-endian format
inline void writeU32BE(uint8_t* dest, uint32_t value) {
    dest[0] = static_cast<uint8_t>((value >> 24) & 0xFF);
    dest[1] = static_cast<uint8_t>((value >> 16) & 0xFF);
    dest[2] = static_cast<uint8_t>((value >> 8) & 0xFF);
    dest[3] = static_cast<uint8_t>(value & 0xFF);
}

// Read uint16_t from little-endian format
inline uint16_t readU16LE(const uint8_t* src) {
    return static_cast<uint16_t>(src[0])
         | (static_cast<uint16_t>(src[1]) << 8);
}

// Read uint16_t from big-endian format
inline uint16_t readU16BE(const uint8_t* src) {
    return (static_cast<uint16_t>(src[0]) << 8)
         | static_cast<uint16_t>(src[1]);
}

// Read uint32_t from little-endian format
inline uint32_t readU32LE(const uint8_t* src) {
    return static_cast<uint32_t>(src[0])
         | (static_cast<uint32_t>(src[1]) << 8)
         | (static_cast<uint32_t>(src[2]) << 16)
         | (static_cast<uint32_t>(src[3]) << 24);
}

// Read uint32_t from big-endian format
inline uint32_t readU32BE(const uint8_t* src) {
    return (static_cast<uint32_t>(src[0]) << 24)
         | (static_cast<uint32_t>(src[1]) << 16)
         | (static_cast<uint32_t>(src[2]) << 8)
         | static_cast<uint32_t>(src[3]);
}

}  // namespace cyphal