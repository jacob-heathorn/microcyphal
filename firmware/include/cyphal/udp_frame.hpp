#pragma once

#include <stdint.h>

#include "ftl/ipv4/udp/payload.hpp"

namespace cyphal {


// Cyphal UDP datagram payload 
class UdpFrame : public ftl::ipv4::udp::Payload {
  public:
    static constexpr std::size_t kHeaderSize = 24;
  
    // Construct with payload data size
    explicit UdpFrame(std::size_t data_size) 
      : ftl::ipv4::udp::Payload(kHeaderSize + data_size) {}
    UdpFrame() = default;

    uint8_t version() const { 
      return (*this->data() & 0xF0) >> 4; 
    }
    void set_version(uint8_t version) {
      version &= 0x0F; // Only keep the lower 4 bits of the input
      *this->data() = (*this->data() & 0x0F) | (version << 4);
    }
  
    // // Access the UDP payload pointer
    // uint8_t* data() noexcept { return front() + kPayloadOffset; }
    // const uint8_t* data() const noexcept { return front() + kPayloadOffset; }
  };

}

static_assert(sizeof(cyphal::UdpFrame) == sizeof(ftl::ipv4::udp::Payload));
