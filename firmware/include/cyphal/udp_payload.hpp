#pragma once

#include <stdint.h>

#include "ftl/data_frame.hpp"

namespace cyphal {


// Cyphal data frame
class UdpPayload : private ftl::DataFrame {
  public:
    // Offsets into the raw frame
    //
    // TODO
    static constexpr std::size_t kPayloadOffset = 0;
  
    // Construct with payload size
    explicit UdpPayload(std::size_t size) : ftl::DataFrame(size) {}
    UdpPayload() = default;
  
    using ftl::DataFrame::size;
    using ftl::DataFrame::operator bool;
  
    // Access the UDP payload pointer
    uint8_t* data() noexcept { return front() + kPayloadOffset; }
    const uint8_t* data() const noexcept { return front() + kPayloadOffset; }
  };

}

static_assert(sizeof(cyphal::UdpPayload) == sizeof(ftl::DataFrame));
