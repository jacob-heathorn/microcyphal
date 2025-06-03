#pragma once

#include <cstdint>
#include <cstddef>

#include "ftl/ipv4/udp/payload.hpp"
#include "cyphal/byte_order.hpp"

namespace cyphal {

//------------------------------------------------------------------------------
// Cyphal UdpFrame
//
// This class encapsulates a Cyphal/UDP datagram payload, including the 24-byte
// header (packed exactly per the Cyphal specification) followed by application
// data and a 4-byte CRC. It uses explicit bit-masks and shifts to place each
// field in the correct byte position regardless of compiler bitfield behavior.
//
// Layout of the 24-byte header (all multi-byte fields are little-endian unless
// otherwise noted):
//  ┌───────────────────────────────────────────────────────────────────────────┐
//  │ byte 0: [  version (4 bits)  │  reserved (4 bits)  ]                     │
//  │ byte 1: [ priority (3 bits) │ reserved (5 bits) ]                        │
//  │ byte 2: source_node_id low byte                                      │
//  │ byte 3: source_node_id high byte                                     │
//  │ byte 4: destination_node_id low byte                                 │
//  │ byte 5: destination_node_id high byte                                │
//  │ byte 6: [ data_specifier (low 8 bits) ]                              │
//  │ byte 7: [ service_not_message (bit 15) │ data_specifier (bits 14:8) ] │
//  │ bytes 8–15: transfer_id (uint64 little-endian)                      │
//  │ bytes 16–19: [ frame_index (bits 0:30) │ end_of_transfer (bit 31) ]  │
//  │ bytes 20–21: user_data (uint16 little-endian)                        │
//  │ bytes 22–23: header_crc16 (uint16 big-endian)                        │
//  └───────────────────────────────────────────────────────────────────────────┘
//
// All “reserved” bits are left as whatever was in memory (or zero if freshly
// constructed). Application code should set all fields explicitly, then compute
// header_crc16 and call set_header_crc16().  
//
// The version field is the low nibble of byte 0. Priority is in bits 7:5 of
// byte 1. This matches libudpard’s packing (so raw byte 0 = 0x01 when version=1).
//------------------------------------------------------------------------------

class UdpFrame final : public ftl::ipv4::udp::Payload {

private:
    // Don't let users get confused by base class accessors.
    using ftl::ipv4::udp::Payload::data;

public:
    static constexpr uint8_t kHeaderVersion = 1;
    static constexpr std::size_t kHeaderSize      = 24;
    static constexpr std::size_t kHeaderCrcSize = 2;
    static constexpr std::size_t kTransferCrcSize = 4;

    // Constructs a UdpFrame with data_size bytes of application data.
    // Total Payload size = header (24) + data_size + transfer_crc (4).
    explicit UdpFrame(std::size_t data_size)
      : ftl::ipv4::udp::Payload(kHeaderSize + data_size + kTransferCrcSize)
    {
        // Zero out the 24-byte header before setting fields.
        memset(data(), 0, kHeaderSize);
        set_version(kHeaderVersion);
    }

    // Default constructs an empty frame (no payload buffer allocated).
    UdpFrame() = default;

    //----------------------------------------------------------------------------
    // — Getters —
    //----------------------------------------------------------------------------

    // uint4 version (low nibble of byte 0)
    uint8_t version() const {
        return data()[0] & 0x0F;
    }

    // uint3 priority (bits 7:5 of byte 1)
    uint8_t priority() const {
        return (data()[1] >> 5) & 0x07;
    }

    // uint16 source_node_id (bytes 2–3, little-endian)
    uint16_t source_node_id() const {
        return readU16LE(data() + 2);
    }

    // uint16 destination_node_id (bytes 4–5, little-endian)
    uint16_t destination_node_id() const {
        return readU16LE(data() + 4);
    }

    // uint15 data_specifier (bits 0:14 of the 16-bit word in bytes 6–7)
    uint16_t data_specifier() const {
        return readU16LE(data() + 6) & 0x7FFF;
    }

    // bool service_not_message (bit 15 of the 16-bit word in bytes 6–7)
    bool service_not_message() const {
        return ((readU16LE(data() + 6) >> 15) & 0x01) != 0;
    }

    // uint64 transfer_id (bytes 8–15, little-endian)
    uint64_t transfer_id() const {
        const uint8_t* d = data() + 8;
        uint64_t v = 0;
        for (int i = 0; i < 8; ++i) {
            v |= static_cast<uint64_t>(d[i]) << (8 * i);
        }
        return v;
    }

    // uint31 frame_index (bits 0:30 of the 32-bit word in bytes 16–19)
    uint32_t frame_index() const {
        return readU32LE(data() + 16) & 0x7FFF'FFFFu;
    }

    // bool end_of_transfer (bit 31 of the 32-bit word in bytes 16–19)
    bool end_of_transfer() const {
        return ((readU32LE(data() + 16) >> 31) & 0x01) != 0;
    }

    // uint16 user_data (bytes 20–21, little-endian)
    uint16_t user_data() const {
        return readU16LE(data() + 20);
    }

    // uint16 header_crc16_big_endian (bytes 22–23, big-endian)
    uint16_t header_crc16() const {
        return readU16BE(data() + 22);
    }

    uint8_t* header() noexcept { return data(); }
    const uint8_t* header() const noexcept { return data(); }

    uint8_t* payload() noexcept { return data() + kHeaderSize; }
    const uint8_t* payload() const noexcept { return data() + kHeaderSize; }
    std::size_t payload_max_size() const noexcept { return size() - kHeaderSize - kTransferCrcSize; }

    //----------------------------------------------------------------------------
    // — Setters —
    //----------------------------------------------------------------------------

    // uint4 version (low nibble of byte 0)
    void set_version(uint8_t v) {
        v &= 0x0F;
        uint8_t& b = data()[0];
        b = (b & 0xF0)  // clear bits 3:0, keep bits 7:4 (reserved)
          |  (v);      // put version into bits 3:0
    }

    // uint3 priority (bits 7:5 of byte 1)
    void set_priority(uint8_t p) {
        p &= 0x07;
        uint8_t& b = data()[1];
        b = (b & 0x1F)      // clear bits 7:5, keep bits 4:0 (reserved)
          | (p << 5);       // put priority into bits 7:5
    }

    // uint16 source_node_id (bytes 2–3, little-endian)
    void set_source_node_id(uint16_t id) {
        writeU16LE(data() + 2, id);
    }

    // uint16 destination_node_id (bytes 4–5, little-endian)
    void set_destination_node_id(uint16_t id) {
        writeU16LE(data() + 4, id);
    }

    // uint15 data_specifier (bits 0:14 of bytes 6–7)
    void set_data_specifier(uint16_t ds) {
        ds &= 0x7FFF;
        uint16_t w = readU16LE(data() + 6);
        w = (w & 0x8000) | ds;  // preserve bit 15, set bits 0:14
        writeU16LE(data() + 6, w);
    }

    // bool service_not_message (bit 15 of bytes 6–7)
    void set_service_not_message(bool s) {
        uint16_t w = readU16LE(data() + 6);
        if (s) {
            w |= 0x8000;
        } else {
            w &= 0x7FFF;
        }
        writeU16LE(data() + 6, w);
    }

    // uint64 transfer_id (bytes 8–15, little-endian)
    void set_transfer_id(uint64_t v) {
        uint8_t* d = data() + 8;
        for (int i = 0; i < 8; ++i) {
            d[i] = static_cast<uint8_t>((v >> (8 * i)) & 0xFF);
        }
    }

    // uint31 frame_index (bits 0:30 of bytes 16–19)
    void set_frame_index(uint32_t idx) {
        idx &= 0x7FFF'FFFFu;
        uint32_t w = readU32LE(data() + 16);
        w = (w & 0x8000'0000u) | idx;  // preserve bit 31, set bits 0:30
        writeU32LE(data() + 16, w);
    }

    // bool end_of_transfer (bit 31 of bytes 16–19)
    void set_end_of_transfer(bool e) {
        uint32_t w = readU32LE(data() + 16);
        if (e) {
            w |= 0x8000'0000u;
        } else {
            w &= 0x7FFF'FFFFu;
        }
        writeU32LE(data() + 16, w);
    }

    // uint16 user_data (bytes 20–21, little-endian)
    void set_user_data(uint16_t u) {
        writeU16LE(data() + 20, u);
    }

    // uint16 header_crc16_big_endian (bytes 22–23, big-endian)
    void set_header_crc16(uint16_t crc) {
        writeU16BE(data() + 22, crc);
    }
};

}  // namespace cyphal

static_assert(sizeof(cyphal::UdpFrame) == sizeof(ftl::ipv4::udp::Payload));
