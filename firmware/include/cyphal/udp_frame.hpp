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
      this->set_version(kHeaderVersion);
    }
    
    // Constructs an empty frame
    UdpFrame() = default;

    uint8_t version() const { 
      return (*this->data() & 0xF0) >> 4; 
    }

  private:
    void set_version(uint8_t version) {
      version &= 0x0F; // Only keep the lower 4 bits of the input
      *this->data() = (*this->data() & 0x0F) | (version << 4);
    }
  };

}

static_assert(sizeof(cyphal::UdpFrame) == sizeof(ftl::ipv4::udp::Payload));
