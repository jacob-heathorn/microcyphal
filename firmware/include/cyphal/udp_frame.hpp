#pragma once

#include <stdint.h>

#include "ftl/ipv4/udp/payload.hpp"

namespace cyphal {


// Cyphal UDP datagram payload 
class UdpFrame : public ftl::ipv4::udp::Payload {
  public:
    static constexpr std::size_t kHeaderSize = 24;
    static constexpr uint8_t kHeaderVersion = 1;
  
    // Constructs with payload data size
    explicit UdpFrame(std::size_t data_size) 
      : ftl::ipv4::udp::Payload(kHeaderSize + data_size) {
      set_version(kHeaderVersion);
    }
    
    // Constructs an empty frame
    UdpFrame() = default;

    //
    // — Getters —
    //

    // uint4 version
    uint8_t version() const {
        return (data()[0] >> 4) & 0x0F;
    }

    // uint3 priority
    uint8_t priority() const {
        return (data()[1] >> 5) & 0x07;
    }

    // uint16 source_node_id
    uint16_t source_node_id() const {
        return uint16_t(data()[2]) | (uint16_t(data()[3]) << 8);
    }

    // uint16 destination_node_id
    uint16_t destination_node_id() const {
        return uint16_t(data()[4]) | (uint16_t(data()[5]) << 8);
    }

    // uint15 data_specifier
    uint16_t data_specifier() const {
        uint16_t w = uint16_t(data()[6]) | (uint16_t(data()[7]) << 8);
        return w & 0x7FFF;
    }

    // bool service_not_message
    bool service_not_message() const {
        uint16_t w = uint16_t(data()[6]) | (uint16_t(data()[7]) << 8);
        return (w >> 15) != 0;
    }

    // uint64 transfer_id
    uint64_t transfer_id() const {
        const uint8_t* d = data() + 8;
        uint64_t v = 0;
        for (int i = 0; i < 8; ++i) {
            v |= uint64_t(d[i]) << (8 * i);
        }
        return v;
    }

    // uint31 frame_index
    uint32_t frame_index() const {
        uint32_t w =  uint32_t(data()[16])
                    | (uint32_t(data()[17]) << 8)
                    | (uint32_t(data()[18]) << 16)
                    | (uint32_t(data()[19]) << 24);
        return w & 0x7FFF'FFFF;
    }

    // bool end_of_transfer
    bool end_of_transfer() const {
        uint32_t w =  uint32_t(data()[16])
                    | (uint32_t(data()[17]) << 8)
                    | (uint32_t(data()[18]) << 16)
                    | (uint32_t(data()[19]) << 24);
        return (w >> 31) != 0;
    }

    // uint16 user_data
    uint16_t user_data() const {
        return uint16_t(data()[20]) | (uint16_t(data()[21]) << 8);
    }

    // uint16 header_crc16_big_endian
    uint16_t header_crc16() const {
        // big-endian
        return (uint16_t(data()[22]) << 8) | uint16_t(data()[23]);
    }

    //
    // — Setters —
    //

    // uint4 version
    void set_version(uint8_t v) {
        v &= 0x0F;
        uint8_t &b = data()[0];
        b = (b & 0x0F) | (v << 4);
    }

    // uint3 priority
    void set_priority(uint8_t p) {
        p &= 0x07;
        uint8_t &b = data()[1];
        b = (b & 0x1F) | (p << 5);
    }

    // uint16 source_node_id
    void set_source_node_id(uint16_t id) {
        uint8_t* d = data();
        d[2] = id & 0xFF;
        d[3] = (id >> 8) & 0xFF;
    }

    // uint16 destination_node_id
    void set_destination_node_id(uint16_t id) {
        uint8_t* d = data();
        d[4] = id & 0xFF;
        d[5] = (id >> 8) & 0xFF;
    }

    // uint15 data_specifier
    void set_data_specifier(uint16_t ds) {
        ds &= 0x7FFF;
        uint16_t w = uint16_t(data()[6]) | (uint16_t(data()[7]) << 8);
        w = (w & 0x8000) | ds;
        data()[6] = w & 0xFF;
        data()[7] = (w >> 8) & 0xFF;
    }

    // bool service_not_message
    void set_service_not_message(bool s) {
        uint16_t w = uint16_t(data()[6]) | (uint16_t(data()[7]) << 8);
        if (s) {
            w |= 0x8000;
        } else {
            w &= 0x7FFF;
        }
        data()[6] = w & 0xFF;
        data()[7] = (w >> 8) & 0xFF;
    }

    // uint64 transfer_id
    void set_transfer_id(uint64_t v) {
        uint8_t* d = data() + 8;
        for (int i = 0; i < 8; ++i) {
            d[i] = (v >> (8 * i)) & 0xFF;
        }
    }

    // uint31 frame_index
    void set_frame_index(uint32_t idx) {
        idx &= 0x7FFF'FFFF;
        uint32_t w =  uint32_t(data()[16])
                    | (uint32_t(data()[17]) << 8)
                    | (uint32_t(data()[18]) << 16)
                    | (uint32_t(data()[19]) << 24);
        w = (w & 0x8000'0000) | idx;
        data()[16] = w & 0xFF;
        data()[17] = (w >> 8) & 0xFF;
        data()[18] = (w >> 16) & 0xFF;
        data()[19] = (w >> 24) & 0xFF;
    }

    // bool end_of_transfer
    void set_end_of_transfer(bool e) {
        uint32_t w =  uint32_t(data()[16])
                    | (uint32_t(data()[17]) << 8)
                    | (uint32_t(data()[18]) << 16)
                    | (uint32_t(data()[19]) << 24);
        if (e) {
            w |= 0x8000'0000;
        } else {
            w &= 0x7FFF'FFFF;
        }
        data()[16] = w & 0xFF;
        data()[17] = (w >> 8) & 0xFF;
        data()[18] = (w >> 16) & 0xFF;
        data()[19] = (w >> 24) & 0xFF;
    }

    // uint16 user_data
    void set_user_data(uint16_t u) {
        uint8_t* d = data();
        d[20] = u & 0xFF;
        d[21] = (u >> 8) & 0xFF;
    }

    // uint16 header_crc16_big_endian
    void set_header_crc16(uint16_t crc) {
        // big-endian
        uint8_t* d = data();
        d[22] = (crc >> 8) & 0xFF;
        d[23] = crc & 0xFF;
    }
};

}
  

static_assert(sizeof(cyphal::UdpFrame) == sizeof(ftl::ipv4::udp::Payload));
