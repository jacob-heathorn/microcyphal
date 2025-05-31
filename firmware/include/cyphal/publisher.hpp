#pragma once

#include <cstdint>
#include <cstring>
#include <utility>  // std::move

#include "cyphal/udp_frame.hpp"
#include "ftl/ipv4/udp/socket.hpp"  // your UDP socket interface

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
        // 1) Serialize the message into a temporary buffer.
        //    We assume MessageT::MAX_PAYLOAD_SIZE is a constexpr bound.

        // TODO preserve:
        // static_assert(MessageT::MAX_PAYLOAD_SIZE <= 65479,
        //               "Payload too large for single‐frame Cyphal/UDP" );
        uint8_t payload_buf[MessageT::MAX_PAYLOAD_SIZE];
        size_t   payload_len = msg.serialize(payload_buf, sizeof(payload_buf));

        // 2) Allocate a Cyphal/UDP frame: header (24) + payload + CRC-32C (4).
        UdpFrame frame(payload_len + /*CRC-32C*/ 4);

        // 3) Fill in the Cyphal/UDP header (24 bytes) :contentReference[oaicite:1]{index=1}:
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

        // 4) Copy the serialized payload right after the 24‐byte header
        std::memcpy(frame.data() + UdpFrame::kHeaderSize,
                    payload_buf, payload_len);

        // 5) Append the 4-byte CRC-32C (little-endian) of the payload :contentReference[oaicite:3]{index=3}
        uint32_t crc32 = crc32c(payload_buf, payload_len);
        auto *crc_ptr  = frame.data() + UdpFrame::kHeaderSize + payload_len;
        crc_ptr[0] =  uint8_t( crc32        & 0xFF);
        crc_ptr[1] =  uint8_t((crc32 >>  8) & 0xFF);
        crc_ptr[2] =  uint8_t((crc32 >> 16) & 0xFF);
        crc_ptr[3] =  uint8_t((crc32 >> 24) & 0xFF);

        // 6) Compute and set the header CRC-16/CCITT-FALSE over bytes 0..21 (big-endian field) :contentReference[oaicite:4]{index=4}
        uint16_t hdr_crc = crc16_ccitt_false_be(frame.data(), /*len=*/22);
        frame.set_header_crc16(hdr_crc);

        // 7) Send via UDP to the Cyphal IPv4 multicast group for this subject
        //    (see spec §4.3.2.1: group = 239.0.0.(subject-id), port = 938296) :contentReference[oaicite:5]{index=5}
        ftl::ipv4::Endpoint ep{/*address=*/make_multicast_address(subject_id_),
                               /*port   =*/938296};
        socket_->send(std::move(frame), ep);
    }

private:
    uint16_t subject_id_;
    ftl::ipv4::udp::SocketPtr socket_;
    uint16_t source_node_id_;
    uint8_t  priority_;
    uint64_t transfer_id_;

    // Helper to compute 239.0.0.<subject-id>:
    static uint32_t make_multicast_address(uint16_t subject_id) {
        // 239.0.0.X  in network‐order: 0xEF000000 | subject_id
        return 0xEF000000u | uint32_t(subject_id);
    }

    // Stub signatures for CRC functions—you’ll need real implementations:
    static uint16_t crc16_ccitt_false_be(const void* data, size_t len);
    static uint32_t crc32c(const void* data, size_t len);
};

}  // namespace cyphal
