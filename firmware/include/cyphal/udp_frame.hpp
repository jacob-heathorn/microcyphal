#pragma once

#include <cstdint>
#include <cstddef>

#include "ftl/ipv4/udp/payload.hpp"

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
public:
    static constexpr std::size_t kHeaderSize      = 24;
    static constexpr std::size_t kTransferCrcSize = 4;

    static constexpr uint8_t kHeaderVersion = 1;

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
        return static_cast<uint16_t>(data()[2])
             | (static_cast<uint16_t>(data()[3]) << 8);
    }

    // uint16 destination_node_id (bytes 4–5, little-endian)
    uint16_t destination_node_id() const {
        return static_cast<uint16_t>(data()[4])
             | (static_cast<uint16_t>(data()[5]) << 8);
    }

    // uint15 data_specifier (bits 0:14 of the 16-bit word in bytes 6–7)
    uint16_t data_specifier() const {
        uint16_t w = static_cast<uint16_t>(data()[6])
                   | (static_cast<uint16_t>(data()[7]) << 8);
        return w & 0x7FFF;
    }

    // bool service_not_message (bit 15 of the 16-bit word in bytes 6–7)
    bool service_not_message() const {
        uint16_t w = static_cast<uint16_t>(data()[6])
                   | (static_cast<uint16_t>(data()[7]) << 8);
        return ((w >> 15) & 0x01) != 0;
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
        uint32_t w =  static_cast<uint32_t>(data()[16])
                    | (static_cast<uint32_t>(data()[17]) << 8)
                    | (static_cast<uint32_t>(data()[18]) << 16)
                    | (static_cast<uint32_t>(data()[19]) << 24);
        return w & 0x7FFF'FFFFu;
    }

    // bool end_of_transfer (bit 31 of the 32-bit word in bytes 16–19)
    bool end_of_transfer() const {
        uint32_t w =  static_cast<uint32_t>(data()[16])
                    | (static_cast<uint32_t>(data()[17]) << 8)
                    | (static_cast<uint32_t>(data()[18]) << 16)
                    | (static_cast<uint32_t>(data()[19]) << 24);
        return ((w >> 31) & 0x01) != 0;
    }

    // uint16 user_data (bytes 20–21, little-endian)
    uint16_t user_data() const {
        return static_cast<uint16_t>(data()[20])
             | (static_cast<uint16_t>(data()[21]) << 8);
    }

    // uint16 header_crc16_big_endian (bytes 22–23, big-endian)
    uint16_t header_crc16() const {
        return (static_cast<uint16_t>(data()[22]) << 8)
             | static_cast<uint16_t>(data()[23]);
    }

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
        uint8_t* d = data();
        d[2] = static_cast<uint8_t>(id & 0xFF);
        d[3] = static_cast<uint8_t>((id >> 8) & 0xFF);
    }

    // uint16 destination_node_id (bytes 4–5, little-endian)
    void set_destination_node_id(uint16_t id) {
        uint8_t* d = data();
        d[4] = static_cast<uint8_t>(id & 0xFF);
        d[5] = static_cast<uint8_t>((id >> 8) & 0xFF);
    }

    // uint15 data_specifier (bits 0:14 of bytes 6–7)
    void set_data_specifier(uint16_t ds) {
        ds &= 0x7FFF;
        uint16_t w = static_cast<uint16_t>(data()[6])
                   | (static_cast<uint16_t>(data()[7]) << 8);
        w = (w & 0x8000) | ds;  // preserve bit 15, set bits 0:14
        data()[6] = static_cast<uint8_t>(w & 0xFF);
        data()[7] = static_cast<uint8_t>((w >> 8) & 0xFF);
    }

    // bool service_not_message (bit 15 of bytes 6–7)
    void set_service_not_message(bool s) {
        uint16_t w = static_cast<uint16_t>(data()[6])
                   | (static_cast<uint16_t>(data()[7]) << 8);
        if (s) {
            w |= 0x8000;
        } else {
            w &= 0x7FFF;
        }
        data()[6] = static_cast<uint8_t>(w & 0xFF);
        data()[7] = static_cast<uint8_t>((w >> 8) & 0xFF);
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
        uint32_t w =  static_cast<uint32_t>(data()[16])
                    | (static_cast<uint32_t>(data()[17]) << 8)
                    | (static_cast<uint32_t>(data()[18]) << 16)
                    | (static_cast<uint32_t>(data()[19]) << 24);
        w = (w & 0x8000'0000u) | idx;  // preserve bit 31, set bits 0:30
        data()[16] = static_cast<uint8_t>(w & 0xFF);
        data()[17] = static_cast<uint8_t>((w >> 8) & 0xFF);
        data()[18] = static_cast<uint8_t>((w >> 16) & 0xFF);
        data()[19] = static_cast<uint8_t>((w >> 24) & 0xFF);
    }

    // bool end_of_transfer (bit 31 of bytes 16–19)
    void set_end_of_transfer(bool e) {
        uint32_t w =  static_cast<uint32_t>(data()[16])
                    | (static_cast<uint32_t>(data()[17]) << 8)
                    | (static_cast<uint32_t>(data()[18]) << 16)
                    | (static_cast<uint32_t>(data()[19]) << 24);
        if (e) {
            w |= 0x8000'0000u;
        } else {
            w &= 0x7FFF'FFFFu;
        }
        data()[16] = static_cast<uint8_t>(w & 0xFF);
        data()[17] = static_cast<uint8_t>((w >> 8) & 0xFF);
        data()[18] = static_cast<uint8_t>((w >> 16) & 0xFF);
        data()[19] = static_cast<uint8_t>((w >> 24) & 0xFF);
    }

    // uint16 user_data (bytes 20–21, little-endian)
    void set_user_data(uint16_t u) {
        uint8_t* d = data();
        d[20] = static_cast<uint8_t>(u & 0xFF);
        d[21] = static_cast<uint8_t>((u >> 8) & 0xFF);
    }

    // uint16 header_crc16_big_endian (bytes 22–23, big-endian)
    void set_header_crc16(uint16_t crc) {
        uint8_t* d = data();
        d[22] = static_cast<uint8_t>((crc >> 8) & 0xFF);
        d[23] = static_cast<uint8_t>(crc & 0xFF);
    }
};

}  // namespace cyphal

static_assert(sizeof(cyphal::UdpFrame) == sizeof(ftl::ipv4::udp::Payload));
