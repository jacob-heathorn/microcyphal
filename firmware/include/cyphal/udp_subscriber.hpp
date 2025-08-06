#pragma once

#include <cassert>
#include <cstdint>
#include <cstring>
#include <optional>

#include "cyphal/udp_frame.hpp"
#include "cyphal/udp_transport.hpp"
#include "cyphal/pool_map.hpp"
#include "ftl/byte_order.hpp"
#include "nunavut/support/serialization.hpp"
#include "etl/crc16_ccitt.h"
#include "etl/crc32_c.h"
#include "ftl/unique_bump_pool.hpp"
#include "ftl/bump_allocator.hpp"

namespace cyphal {

template <typename MessageT>
class UdpSubscriber {
public:
    /// Initialize the shared memory pool for duplicate detection
    /// Must be called before creating any UdpSubscriber instances
    /// @param allocator The bump allocator to use for node storage
    ///                  The pool will grow dynamically as needed until this allocator runs out of memory
    static void initializePool(ftl::BumpAllocator& allocator) {
        // Initialize the PoolMap's internal shared pool
        PoolMap<uint16_t, uint64_t>::initializePool(allocator);
    }
    
    /// @param subject_id      The Cyphal subject-ID to subscribe to (0…8191).
    /// @param node_id         Your node-ID (0…65534; 65535 = anonymous).
    /// @param transport       Reference to UdpTransport that manages the socket.
    UdpSubscriber(uint16_t subject_id,
                  uint16_t node_id,
                  UdpTransport& transport)
        : subject_id_(subject_id)
        , node_id_(node_id)
        , transport_(transport)
        , last_transfer_ids_()  // PoolMap will use its internal shared pool
    {
        // Join the multicast group for this subject
        transport_.joinMulticastGroup(subject_id_);
    }
    
    /// Receive and deserialize a message if available.
    /// Returns std::nullopt if no message available or on error.
    std::optional<MessageT> receive() {
        ftl::ipv4::Endpoint sender;
        auto payload = transport_.getSocket()->receive(&sender);
        
        if (!payload) {
            return std::nullopt;  // No data available
        }
        
        const size_t received_bytes = payload.size();
        
        // Validate minimum frame size
        if (received_bytes < UdpFrame::kHeaderSize + UdpFrame::kTransferCrcSize) {
            return std::nullopt;  // Frame too small
        }
        
        const uint8_t* data = payload.front();
        
        // Verify header CRC (bytes 22-23, big-endian)
        const uint16_t received_header_crc = ftl::ReadU16BE(data + UdpFrame::kHeaderSize - UdpFrame::kHeaderCrcSize);
        const uint16_t computed_header_crc = etl::crc16_ccitt(data, data + UdpFrame::kHeaderSize - UdpFrame::kHeaderCrcSize);
        
        if (received_header_crc != computed_header_crc) {
            return std::nullopt;  // Header CRC mismatch
        }
        
        // Parse header fields
        const uint8_t version = data[0] & 0x0F;
        if (version != UdpFrame::kHeaderVersion) {
            return std::nullopt;  // Unsupported version
        }
        
        // const uint8_t priority = (data[1] >> 5) & 0x07;  // Currently unused
        const uint16_t source_node_id = ftl::ReadU16LE(data + 2);
        const uint16_t destination_node_id = ftl::ReadU16LE(data + 4);
        
        // Check if message is for us (broadcast or our node ID)
        if (destination_node_id != 0xFFFF && destination_node_id != node_id_) {
            return std::nullopt;  // Not for us
        }
        
        // Extract data specifier and service flag
        const uint16_t data_specifier = ftl::ReadU16LE(data + 6) & 0x7FFF;
        const bool is_service = (data[7] & 0x80) != 0;
        
        // We only handle message transfers, not service transfers
        if (is_service) {
            return std::nullopt;
        }
        
        // Check if this is the subject we're subscribed to
        if (data_specifier != subject_id_) {
            return std::nullopt;  // Different subject
        }
        
        // Extract transfer metadata
        const uint64_t transfer_id = ftl::ReadU64LE(data + 8);
        const uint32_t frame_index_eot = ftl::ReadU32LE(data + 16);
        const uint32_t frame_index = frame_index_eot & 0x7FFFFFFF;
        const bool end_of_transfer = (frame_index_eot & 0x80000000) != 0;
        
        // For now, we only handle single-frame transfers
        if (frame_index != 0 || !end_of_transfer) {
            // TODO: Add multi-frame support with reassembly
            return std::nullopt;
        }
        
        // Check for duplicate transfer using pool-based map
        auto* last_id = last_transfer_ids_.find(source_node_id);
        if (last_id && *last_id == transfer_id) {
            return std::nullopt;  // Duplicate transfer
        }
        
        // Update the transfer ID for this source node
        // If pool is exhausted, oldest entries will remain (not ideal but safe)
        last_transfer_ids_.insert(source_node_id, transfer_id);
        
        // Calculate payload size (total - header - CRC)
        const size_t payload_size = received_bytes - UdpFrame::kHeaderSize - UdpFrame::kTransferCrcSize;
        const uint8_t* payload_data = data + UdpFrame::kHeaderSize;
        
        // Verify payload CRC (last 4 bytes, little-endian)
        const uint32_t received_payload_crc = ftl::ReadU32LE(data + received_bytes - UdpFrame::kTransferCrcSize);
        const uint32_t computed_payload_crc = etl::crc32_c(payload_data, payload_data + payload_size);
        
        if (received_payload_crc != computed_payload_crc) {
            return std::nullopt;  // Payload CRC mismatch
        }
        
        // Deserialize the message
        MessageT msg;
        nunavut::support::const_bitspan payload_span{payload_data, payload_size};
        
        const nunavut::support::SerializeResult result = deserialize(msg, payload_span);
        if (result < 0) {
            return std::nullopt;  // Deserialization failed
        }
        
        return msg;
    }
    

private:
    uint16_t subject_id_;
    uint16_t node_id_;
    UdpTransport& transport_;
    
    // Use pool-based map for duplicate detection
    // This map shares a memory pool with all other UdpSubscriber instances
    PoolMap<uint16_t, uint64_t> last_transfer_ids_;
};


}  // namespace cyphal