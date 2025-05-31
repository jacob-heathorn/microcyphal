//
// This is an AUTO-GENERATED Cyphal DSDL data type implementation. Curious? See https://opencyphal.org.
// You shouldn't attempt to edit this file.
//
// Generator     : nunavut-3.0.0.dev1 (serialization was enabled)
// Source file   : 7510.List.1.0.dsdl
// Is deprecated : no
// Fixed port-ID : 7510
// Full name     : uavcan.node.port.List
// Type Version  : 1.0
//
// Resource Generation
//    Support Namespace : nunavut.support
//    Support Version   : (1, 0, 0)
//
// Platform
//     python_version : 3.10.12
//
// Language
//     name         : cpp
//     experimental : True
//
// Language Options
//     target_endianness                       : any
//     omit_float_serialization_support        : False
//     omit_serialization_support              : False
//     enable_serialization_asserts            : False
//     enable_override_variable_array_capacity : False
//     std                                     : c++14
//     std_flavor                              : std
//     cast_format                             : static_cast<{type}>({value})
//     variable_array_type_include             : <vector>
//     variable_array_type_template            : std::vector<{TYPE}>
//     variable_array_type_constructor_args    :
//     allocator_include                       :
//     allocator_type                          :
//     allocator_is_default_constructible      : True
//     ctor_convention                         : default
//     variant_include                         :
//
// Uses Language Features
//     Uses std_variant:no
//
#ifndef UAVCAN_NODE_PORT_LIST_1_0_HPP_INCLUDED
#define UAVCAN_NODE_PORT_LIST_1_0_HPP_INCLUDED

#include "nunavut/support/serialization.hpp"
#include "uavcan/node/port/ServiceIDList_1_0.hpp"
#include "uavcan/node/port/SubjectIDList_1_0.hpp"
#include <cstdint>
#include <limits>

namespace uavcan
{
namespace node
{
namespace port
{
// +-------------------------------------------------------------------------------------------------------------------+
// | LANGUAGE OPTION ASSERTIONS
// |    These static assertions ensure that the header is being used with
// | Nunavut C++ serialization support that is compatible with the language
// | options in effect when that support code was generated.
// +-------------------------------------------------------------------------------------------------------------------+
static_assert( nunavut::support::options::target_endianness == 1693710260,
              "uavcan.node.port.List.1.0"
              "is trying to use a serialization library that was compiled with "
              "different language options. This is dangerous and therefore not "
              "allowed." );
static_assert( nunavut::support::options::omit_float_serialization_support == 0,
              "uavcan.node.port.List.1.0"
              "is trying to use a serialization library that was compiled with "
              "different language options. This is dangerous and therefore not "
              "allowed." );
static_assert( nunavut::support::options::omit_serialization_support == 0,
              "uavcan.node.port.List.1.0"
              "is trying to use a serialization library that was compiled with "
              "different language options. This is dangerous and therefore not "
              "allowed." );
static_assert( nunavut::support::options::enable_serialization_asserts == 0,
              "uavcan.node.port.List.1.0"
              "is trying to use a serialization library that was compiled with "
              "different language options. This is dangerous and therefore not "
              "allowed." );
static_assert( nunavut::support::options::enable_override_variable_array_capacity == 0,
              "uavcan.node.port.List.1.0"
              "is trying to use a serialization library that was compiled with "
              "different language options. This is dangerous and therefore not "
              "allowed." );
static_assert( nunavut::support::options::std == 3161622713,
              "uavcan.node.port.List.1.0"
              "is trying to use a serialization library that was compiled with "
              "different language options. This is dangerous and therefore not "
              "allowed." );
static_assert( nunavut::support::options::std_flavor == 2826573480,
              "uavcan.node.port.List.1.0"
              "is trying to use a serialization library that was compiled with "
              "different language options. This is dangerous and therefore not "
              "allowed." );
static_assert( nunavut::support::options::cast_format == 1407868567,
              "uavcan.node.port.List.1.0"
              "is trying to use a serialization library that was compiled with "
              "different language options. This is dangerous and therefore not "
              "allowed." );
static_assert( nunavut::support::options::variable_array_type_include == 3320664631,
              "uavcan.node.port.List.1.0"
              "is trying to use a serialization library that was compiled with "
              "different language options. This is dangerous and therefore not "
              "allowed." );
static_assert( nunavut::support::options::variable_array_type_template == 4227611599,
              "uavcan.node.port.List.1.0"
              "is trying to use a serialization library that was compiled with "
              "different language options. This is dangerous and therefore not "
              "allowed." );
static_assert( nunavut::support::options::variable_array_type_constructor_args == 0,
              "uavcan.node.port.List.1.0"
              "is trying to use a serialization library that was compiled with "
              "different language options. This is dangerous and therefore not "
              "allowed." );
static_assert( nunavut::support::options::allocator_include == 0,
              "uavcan.node.port.List.1.0"
              "is trying to use a serialization library that was compiled with "
              "different language options. This is dangerous and therefore not "
              "allowed." );
static_assert( nunavut::support::options::allocator_type == 0,
              "uavcan.node.port.List.1.0"
              "is trying to use a serialization library that was compiled with "
              "different language options. This is dangerous and therefore not "
              "allowed." );
static_assert( nunavut::support::options::allocator_is_default_constructible == 1,
              "uavcan.node.port.List.1.0"
              "is trying to use a serialization library that was compiled with "
              "different language options. This is dangerous and therefore not "
              "allowed." );
static_assert( nunavut::support::options::ctor_convention == 3814588639,
              "uavcan.node.port.List.1.0"
              "is trying to use a serialization library that was compiled with "
              "different language options. This is dangerous and therefore not "
              "allowed." );
static_assert( nunavut::support::options::variant_include == 0,
              "uavcan.node.port.List.1.0"
              "is trying to use a serialization library that was compiled with "
              "different language options. This is dangerous and therefore not "
              "allowed." );


// +-------------------------------------------------------------------------------------------------------------------+
// | This implementation uses a minimal variant implementation that is forward-compatible with the same types generated
// | using the C++17 variant type in the standard library. This minimal variant implementation is limited in the
// | following ways:
// |    1. Supports only emplace and get_if.
// |    2. Only support access by index (see the IndexOf property of the VariantType).
// |    3. This object cannot be copy-constructed nor move-constructed.
// |    4. There is an O(n) lookup in this object's destructor and in the
// |       emplace method.
// |
// | The C++17 version of this object will define the same emplace and get_if wrappers so code written against this
// | version will be fully-forward compatible, but the C++17 version exposes the variant type directly allowing full
// | use of that standard library feature – it is therefore not backwards-compatible.
// +-------------------------------------------------------------------------------------------------------------------+
///
/// A list of ports that this node is using:
/// - Subjects published by this node (whether periodically or ad-hoc).
/// - Subjects that this node is subscribed to (a datalogger or a debugger would typically subscribe to all subjects).
/// - RPC services consumed by this node (i.e., service clients).
/// - RPC services provided by this node (i.e., service servers).
/// 
/// All nodes should implement this capability to provide network introspection and diagnostic capabilities.
/// This message should be published using the fixed subject-ID as follows:
/// - At the OPTIONAL priority level at least every MAX_PUBLICATION_PERIOD seconds.
/// - At the OPTIONAL or SLOW priority level within MAX_PUBLICATION_PERIOD after the port configuration is changed.
///
struct List_1_0 final
{

    struct _traits_  // The name is surrounded with underscores to avoid collisions with DSDL attributes.
    {
        _traits_() = delete;
        static constexpr bool HasFixedPortID = true;
        static constexpr std::uint16_t FixedPortId = 7510U;
        static constexpr bool IsServiceType = false;

        static constexpr const char* FullNameAndVersion() { return "uavcan.node.port.List.1.0"; }
    
        /// Extent is the minimum amount of memory required to hold any serialized representation of any compatible
        /// version of the data type; or, on other words, it is the the maximum possible size of received objects of this type.
        /// The size is specified in bytes (rather than bits) because by definition, extent is an integer number of bytes long.
        /// When allocating a deserialization (RX) buffer for this data type, it should be at least extent bytes large.
        /// When allocating a serialization (TX) buffer, it is safe to use the size of the largest serialized representation
        /// instead of the extent because it provides a tighter bound of the object size; it is safe because the concrete type
        /// is always known during serialization (unlike deserialization). If not sure, use extent everywhere.
        static constexpr std::size_t ExtentBytes                  = 8466UL;
        static constexpr std::size_t SerializationBufferSizeBytes = 8466UL;
        static_assert(ExtentBytes >= SerializationBufferSizeBytes, "Internal constraint violation");
        static_assert(ExtentBytes < (std::numeric_limits<std::size_t>::max() / 8U), "This message is too large to be handled by the selected types");
        struct TypeOf
        {
            TypeOf() = delete;
            using publishers = uavcan::node::port::SubjectIDList_1_0;
            using subscribers = uavcan::node::port::SubjectIDList_1_0;
            using clients = uavcan::node::port::ServiceIDList_1_0;
            using servers = uavcan::node::port::ServiceIDList_1_0;
        };
    };

    
    // +---------------------------------------------------------------------------------------------------------------+
    // | CONSTANTS
    // +---------------------------------------------------------------------------------------------------------------+
    ///
    /// [seconds]
    /// If the port configuration is not updated in this amount of time, the node should publish this message anyway.
    ///
    static constexpr std::uint8_t MAX_PUBLICATION_PERIOD = 10U;
    
    // +----------------------------------------------------------------------+
    // | FIELDS
    // +----------------------------------------------------------------------+
    
    _traits_::TypeOf::publishers publishers{};
    
    _traits_::TypeOf::subscribers subscribers{};
    
    _traits_::TypeOf::clients clients{};
    
    _traits_::TypeOf::servers servers{};
};


inline nunavut::support::SerializeResult serialize(const List_1_0& obj,
                                                   nunavut::support::bitspan out_buffer)
{
    const std::size_t capacity_bits = out_buffer.size();
    if ((static_cast<std::size_t>(capacity_bits)) < 67728UL)
    {
        return -nunavut::support::Error::SerializationBufferTooSmall;
    }
    // Notice that fields that are not an integer number of bytes long may overrun the space allocated for them
    // in the serialization buffer up to the next byte boundary. This is by design and is guaranteed to be safe.
    {   // uavcan.node.port.SubjectIDList.1.0 publishers
        std::size_t _size_bytes0_ = 1025UL;  // Nested object (max) size, in bytes.
        // Reserve space for the delimiter header.
        auto _subspan0_ = out_buffer.subspan(32U, _size_bytes0_ * 8U);
        if(not _subspan0_){
            return -_subspan0_.error();
        }
        auto _err0_ = serialize(obj.publishers, _subspan0_.value());
        if (not _err0_)
        {
            return _err0_;
        }
        _size_bytes0_ = _err0_.value();
        // It is assumed that we know the exact type of the serialized entity, hence we expect the size to match.
        // Jump back to write the delimiter header after the nested object is serialized and its length is known.
        const auto _result3_ = out_buffer.setUxx(_size_bytes0_, 32U);
        if(not _result3_){
            return -_result3_.error();
        }
        out_buffer.add_offset(32U);
        out_buffer.add_offset(_size_bytes0_ * 8U);
        //
    }
    {
        const auto _result0_ = out_buffer.padAndMoveToAlignment(8U);
        if(not _result0_){
            return -_result0_.error();
        }
    }
    {   // uavcan.node.port.SubjectIDList.1.0 subscribers
        std::size_t _size_bytes0_ = 1025UL;  // Nested object (max) size, in bytes.
        // Reserve space for the delimiter header.
        auto _subspan0_ = out_buffer.subspan(32U, _size_bytes0_ * 8U);
        if(not _subspan0_){
            return -_subspan0_.error();
        }
        auto _err0_ = serialize(obj.subscribers, _subspan0_.value());
        if (not _err0_)
        {
            return _err0_;
        }
        _size_bytes0_ = _err0_.value();
        // It is assumed that we know the exact type of the serialized entity, hence we expect the size to match.
        // Jump back to write the delimiter header after the nested object is serialized and its length is known.
        const auto _result3_ = out_buffer.setUxx(_size_bytes0_, 32U);
        if(not _result3_){
            return -_result3_.error();
        }
        out_buffer.add_offset(32U);
        out_buffer.add_offset(_size_bytes0_ * 8U);
        //
    }
    {
        const auto _result0_ = out_buffer.padAndMoveToAlignment(8U);
        if(not _result0_){
            return -_result0_.error();
        }
    }
    {   // uavcan.node.port.ServiceIDList.1.0 clients
        std::size_t _size_bytes0_ = 64UL;  // Nested object (max) size, in bytes.
        // Reserve space for the delimiter header.
        auto _subspan0_ = out_buffer.subspan(32U, _size_bytes0_ * 8U);
        if(not _subspan0_){
            return -_subspan0_.error();
        }
        auto _err0_ = serialize(obj.clients, _subspan0_.value());
        if (not _err0_)
        {
            return _err0_;
        }
        _size_bytes0_ = _err0_.value();
        // It is assumed that we know the exact type of the serialized entity, hence we expect the size to match.
        // Jump back to write the delimiter header after the nested object is serialized and its length is known.
        const auto _result3_ = out_buffer.setUxx(_size_bytes0_, 32U);
        if(not _result3_){
            return -_result3_.error();
        }
        out_buffer.add_offset(32U);
        out_buffer.add_offset(_size_bytes0_ * 8U);
        //
    }
    {
        const auto _result0_ = out_buffer.padAndMoveToAlignment(8U);
        if(not _result0_){
            return -_result0_.error();
        }
    }
    {   // uavcan.node.port.ServiceIDList.1.0 servers
        std::size_t _size_bytes0_ = 64UL;  // Nested object (max) size, in bytes.
        // Reserve space for the delimiter header.
        auto _subspan0_ = out_buffer.subspan(32U, _size_bytes0_ * 8U);
        if(not _subspan0_){
            return -_subspan0_.error();
        }
        auto _err0_ = serialize(obj.servers, _subspan0_.value());
        if (not _err0_)
        {
            return _err0_;
        }
        _size_bytes0_ = _err0_.value();
        // It is assumed that we know the exact type of the serialized entity, hence we expect the size to match.
        // Jump back to write the delimiter header after the nested object is serialized and its length is known.
        const auto _result3_ = out_buffer.setUxx(_size_bytes0_, 32U);
        if(not _result3_){
            return -_result3_.error();
        }
        out_buffer.add_offset(32U);
        out_buffer.add_offset(_size_bytes0_ * 8U);
        //
    }
    {
        const auto _result0_ = out_buffer.padAndMoveToAlignment(8U);
        if(not _result0_){
            return -_result0_.error();
        }
    }
    // It is assumed that we know the exact type of the serialized entity, hence we expect the size to match.
    return out_buffer.offset_bytes_ceil();
}

inline nunavut::support::SerializeResult deserialize(List_1_0& obj,
                                                     nunavut::support::const_bitspan in_buffer)
{
    const auto capacity_bits = in_buffer.size();
    // uavcan.node.port.SubjectIDList.1.0 publishers
    {
        std::size_t _size_bytes1_ = in_buffer.size() / 8U;
        // Delimiter header: truncated uint32
        _size_bytes1_ = in_buffer.getU32(32U);
        in_buffer.add_offset(32U);
        if ((_size_bytes1_ * 8U) > in_buffer.size())
        {
            return -nunavut::support::Error::RepresentationBadDelimiterHeader;
        }
        const std::size_t _dh0_ = _size_bytes1_;
        {
            const auto _err1_ = deserialize(obj.publishers, in_buffer.subspan(0U, _dh0_ * 8U));
            if(_err1_){
                _size_bytes1_ = _err1_.value();
            }else{
                return -_err1_.error();
            }
        }
        // Advance the offset by the size of the delimiter header, even if the nested deserialization routine
        // consumed fewer bytes of data. This behavior implements the implicit truncation rule for nested objects.
        in_buffer.add_offset(_dh0_ * 8U);
    }
    in_buffer.align_offset_to<8U>();
    // uavcan.node.port.SubjectIDList.1.0 subscribers
    {
        std::size_t _size_bytes1_ = in_buffer.size() / 8U;
        // Delimiter header: truncated uint32
        _size_bytes1_ = in_buffer.getU32(32U);
        in_buffer.add_offset(32U);
        if ((_size_bytes1_ * 8U) > in_buffer.size())
        {
            return -nunavut::support::Error::RepresentationBadDelimiterHeader;
        }
        const std::size_t _dh0_ = _size_bytes1_;
        {
            const auto _err1_ = deserialize(obj.subscribers, in_buffer.subspan(0U, _dh0_ * 8U));
            if(_err1_){
                _size_bytes1_ = _err1_.value();
            }else{
                return -_err1_.error();
            }
        }
        // Advance the offset by the size of the delimiter header, even if the nested deserialization routine
        // consumed fewer bytes of data. This behavior implements the implicit truncation rule for nested objects.
        in_buffer.add_offset(_dh0_ * 8U);
    }
    in_buffer.align_offset_to<8U>();
    // uavcan.node.port.ServiceIDList.1.0 clients
    {
        std::size_t _size_bytes1_ = in_buffer.size() / 8U;
        // Delimiter header: truncated uint32
        _size_bytes1_ = in_buffer.getU32(32U);
        in_buffer.add_offset(32U);
        if ((_size_bytes1_ * 8U) > in_buffer.size())
        {
            return -nunavut::support::Error::RepresentationBadDelimiterHeader;
        }
        const std::size_t _dh0_ = _size_bytes1_;
        {
            const auto _err1_ = deserialize(obj.clients, in_buffer.subspan(0U, _dh0_ * 8U));
            if(_err1_){
                _size_bytes1_ = _err1_.value();
            }else{
                return -_err1_.error();
            }
        }
        // Advance the offset by the size of the delimiter header, even if the nested deserialization routine
        // consumed fewer bytes of data. This behavior implements the implicit truncation rule for nested objects.
        in_buffer.add_offset(_dh0_ * 8U);
    }
    in_buffer.align_offset_to<8U>();
    // uavcan.node.port.ServiceIDList.1.0 servers
    {
        std::size_t _size_bytes1_ = in_buffer.size() / 8U;
        // Delimiter header: truncated uint32
        _size_bytes1_ = in_buffer.getU32(32U);
        in_buffer.add_offset(32U);
        if ((_size_bytes1_ * 8U) > in_buffer.size())
        {
            return -nunavut::support::Error::RepresentationBadDelimiterHeader;
        }
        const std::size_t _dh0_ = _size_bytes1_;
        {
            const auto _err1_ = deserialize(obj.servers, in_buffer.subspan(0U, _dh0_ * 8U));
            if(_err1_){
                _size_bytes1_ = _err1_.value();
            }else{
                return -_err1_.error();
            }
        }
        // Advance the offset by the size of the delimiter header, even if the nested deserialization routine
        // consumed fewer bytes of data. This behavior implements the implicit truncation rule for nested objects.
        in_buffer.add_offset(_dh0_ * 8U);
    }
    in_buffer.align_offset_to<8U>();
    auto _bits_got_ = std::min<std::size_t>(in_buffer.offset(), capacity_bits);
    return { static_cast<std::size_t>(_bits_got_ / 8U) };
}

} // namespace port
} // namespace node
} // namespace uavcan

#endif // UAVCAN_NODE_PORT_LIST_1_0_HPP_INCLUDED
