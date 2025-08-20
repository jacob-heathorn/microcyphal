#pragma once

#include <cstdint>
#include <utility>
#include "ftl/ethernet/interface.hpp"
#include "ftl/ipv4/udp/socket.hpp"
#include "cyphal/udp_frame.hpp"

namespace cyphal {

class UdpTransport {
public:
    static constexpr uint16_t kCyphalPort = 9382;
    
    explicit UdpTransport(ftl::ethernet::Interface& interface)
        : interface_(interface)
        , socket_(interface.CreateUdpSocket()) {
        if (!socket_->open()) {
            // Handle error - for now just assert
            assert(false && "Failed to open UDP socket");
        }
        
        if (!socket_->bind(kCyphalPort)) {
            // Handle error - for now just assert
            assert(false && "Failed to bind to Cyphal port");
        }
    }
    
    void send(UdpFrame&& frame, uint16_t subject_id) {
        ftl::ipv4::Endpoint ep{
            ftl::ipv4::Address(makeMulticastAddress(subject_id)), 
            kCyphalPort
        };
        socket_->send(std::move(frame), ep);
    }
    
    void joinMulticastGroup(uint16_t subject_id) {
        const uint32_t multicast_addr = makeMulticastAddress(subject_id);
        socket_->join_multicast_group(ftl::ipv4::Address(multicast_addr));
    }
    
    ftl::ipv4::udp::SocketPtr& getSocket() {
        return socket_;
    }
    
    ftl::ipv4::udp::Payload receive(ftl::ipv4::Endpoint* sender = nullptr) {
        return socket_->receive(sender);
    }

private:
    ftl::ethernet::Interface& interface_;
    ftl::ipv4::udp::SocketPtr socket_;
    
    static uint32_t makeMulticastAddress(uint16_t subject_id) {
        // 0xEF000000 = 239.0.0.0 in big-endian
        return 0xEF000000u | uint32_t(subject_id);
    }
};

}  // namespace cyphal