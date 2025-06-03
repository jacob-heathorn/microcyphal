#pragma once

#include <cassert>
#include <cstdint>
#include <cstring>
#include <utility>  // std::move

#include "cyphal/udp_frame.hpp"
#include "ftl/byte_order.hpp"
#include "ftl/ipv4/udp/socket.hpp"  // your UDP socket interface
#include "nunavut/support/serialization.hpp"
#include "etl/crc16_ccitt.h"
#include "etl/crc32_c.h"


namespace cyphal {

template <typename MessageT>
class UdpPublisher {
public:
    /// @param subject_id      The Cyphal subject-ID (0…8191).
    /// @param socket          An already-opened UDP socket.
    /// @param source_node_id  Your node-ID (0…65534; 65535 = anonymous :contentReference[oaicite:0]{index=0}).
    /// @param priority        Cyphal priority 0 (highest) … 7 (lowest).
    UdpPublisher(uint16_t subject_id,
              ftl::ipv4::udp::SocketPtr socket,
              uint16_t source_node_id,
              uint8_t  priority = 0)
      : subject_id_(subject_id)
      , socket_{std::move(socket)}
      , source_node_id_(source_node_id)
      , priority_(priority & 0x07)
      , transfer_id_(0)
    {
        // bind or open the socket as needed (not shown)
    }

    /// Publish one message as a single‐frame Cyphal/UDP transfer.
    void publish(const MessageT &msg) {
        // Create udp frame, with exact size.
        UdpFrame frame(MessageT::_traits_::SerializationBufferSizeBytes);


        // Serialize into the frame's payload with nanavut.
        // Use explicit cast to avoid constructor ambiguity in bitspan
        nunavut::support::bitspan payload_span{static_cast<uint8_t*>(frame.payload()), frame.payload_max_size()};

        const nunavut::support::SerializeResult result = serialize(msg, payload_span);
        assert(result >= 0 && "Cyphal serialization failed");
        
        // Verify serialization returned the expected size
        const size_t expected_size = MessageT::_traits_::SerializationBufferSizeBytes;
        assert(static_cast<size_t>(result.value()) == expected_size && "Serialization size mismatch");
        assert(expected_size == frame.payload_max_size());

        // Fill in the Cyphal/UDP header (24 bytes) :contentReference[oaicite:1]{index=1}:
        frame.set_version    (UdpFrame::kHeaderVersion);      // uint4
        frame.set_priority   (priority_);                      // uint3
        frame.set_source_node_id     (source_node_id_);       // uint16
        frame.set_destination_node_id(0xFFFF);                // broadcast (65535) :contentReference[oaicite:2]{index=2}
        frame.set_data_specifier     (subject_id_);           // uint15
        frame.set_service_not_message(false);                 // message transfer
        frame.set_transfer_id        (transfer_id_++);        // uint64
        frame.set_frame_index        (0);                     // single‐frame
        frame.set_end_of_transfer    (true);                  // EOT
        frame.set_user_data          (0);                     // application‐opaque

        // Header CRC in the big endian format. Optimization prospect noted from Udpard repository:
        // the header up to frame_index is constant in multi-frame transfers, so we don't really
        // need to recompute the CRC from scratch per frame.
        const uint16_t header_crc = etl::crc16_ccitt(frame.header(), frame.header() + cyphal::UdpFrame::kHeaderSize - cyphal::UdpFrame::kHeaderCrcSize);
        
        // Write header CRC in big-endian format
        ftl::WriteU16BE(frame.header() + cyphal::UdpFrame::kHeaderSize - cyphal::UdpFrame::kHeaderCrcSize, header_crc);

        // Append the 4-byte CRC-32C (little-endian) of the payload.
        const uint32_t payload_crc = etl::crc32_c(frame.payload(), frame.payload() + expected_size);
        
        // Write payload CRC in little-endian format
        ftl::WriteU32LE(frame.payload() + expected_size, payload_crc);

        // Send via UDP to the Cyphal IPv4 multicast group for this subject
        //    (see spec §4.3.2.1: group = 239.0.0.(subject-id), port = 938296)
        ftl::ipv4::Endpoint ep{ftl::ipv4::Address(make_multicast_address(subject_id_)), uint16_t(9382)};
        socket_->send(std::move(frame), ep);
    }

private:
    uint16_t subject_id_;
    ftl::ipv4::udp::SocketPtr socket_;
    uint16_t source_node_id_;
    uint8_t  priority_;
    uint64_t transfer_id_;

    // Helper to compute 239.0.(subject_id >> 8).(subject_id & 0xFF):
    static uint32_t make_multicast_address(uint16_t subject_id) {
        // 0xEF000000 = 239.0.0.0 in big-endian.  
        // OR’ing in subject_id places the high byte of subject_id into
        // the third octet, and the low byte into the fourth octet.
        return 0xEF000000u | uint32_t(subject_id);
    }
};


}  // namespace cyphal
