//
// This is an AUTO-GENERATED Cyphal DSDL data type implementation. Curious? See https://opencyphal.org.
// You shouldn't attempt to edit this file.
//
// Generator     : nunavut-3.0.0.dev1 (serialization was enabled)
// Source file   : Mode.1.0.dsdl
// Is deprecated : no
// Fixed port-ID : None
// Full name     : uavcan.node.Mode
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
//     std                                     : c++17
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
//     Uses std_variant:yes
//
#ifndef UAVCAN_NODE_MODE_1_0_HPP_INCLUDED
#define UAVCAN_NODE_MODE_1_0_HPP_INCLUDED

#include "nunavut/support/serialization.hpp"
#include <cstdint>
#include <limits>

namespace uavcan
{
namespace node
{
// +-------------------------------------------------------------------------------------------------------------------+
// | LANGUAGE OPTION ASSERTIONS
// |    These static assertions ensure that the header is being used with
// | Nunavut C++ serialization support that is compatible with the language
// | options in effect when that support code was generated.
// +-------------------------------------------------------------------------------------------------------------------+
static_assert( nunavut::support::options::target_endianness == 1693710260,
              "uavcan.node.Mode.1.0"
              "is trying to use a serialization library that was compiled with "
              "different language options. This is dangerous and therefore not "
              "allowed." );
static_assert( nunavut::support::options::omit_float_serialization_support == 0,
              "uavcan.node.Mode.1.0"
              "is trying to use a serialization library that was compiled with "
              "different language options. This is dangerous and therefore not "
              "allowed." );
static_assert( nunavut::support::options::omit_serialization_support == 0,
              "uavcan.node.Mode.1.0"
              "is trying to use a serialization library that was compiled with "
              "different language options. This is dangerous and therefore not "
              "allowed." );
static_assert( nunavut::support::options::enable_serialization_asserts == 0,
              "uavcan.node.Mode.1.0"
              "is trying to use a serialization library that was compiled with "
              "different language options. This is dangerous and therefore not "
              "allowed." );
static_assert( nunavut::support::options::enable_override_variable_array_capacity == 0,
              "uavcan.node.Mode.1.0"
              "is trying to use a serialization library that was compiled with "
              "different language options. This is dangerous and therefore not "
              "allowed." );
static_assert( nunavut::support::options::std == 628873475,
              "uavcan.node.Mode.1.0"
              "is trying to use a serialization library that was compiled with "
              "different language options. This is dangerous and therefore not "
              "allowed." );
static_assert( nunavut::support::options::std_flavor == 2826573480,
              "uavcan.node.Mode.1.0"
              "is trying to use a serialization library that was compiled with "
              "different language options. This is dangerous and therefore not "
              "allowed." );
static_assert( nunavut::support::options::cast_format == 1407868567,
              "uavcan.node.Mode.1.0"
              "is trying to use a serialization library that was compiled with "
              "different language options. This is dangerous and therefore not "
              "allowed." );
static_assert( nunavut::support::options::variable_array_type_include == 3320664631,
              "uavcan.node.Mode.1.0"
              "is trying to use a serialization library that was compiled with "
              "different language options. This is dangerous and therefore not "
              "allowed." );
static_assert( nunavut::support::options::variable_array_type_template == 4227611599,
              "uavcan.node.Mode.1.0"
              "is trying to use a serialization library that was compiled with "
              "different language options. This is dangerous and therefore not "
              "allowed." );
static_assert( nunavut::support::options::variable_array_type_constructor_args == 0,
              "uavcan.node.Mode.1.0"
              "is trying to use a serialization library that was compiled with "
              "different language options. This is dangerous and therefore not "
              "allowed." );
static_assert( nunavut::support::options::allocator_include == 0,
              "uavcan.node.Mode.1.0"
              "is trying to use a serialization library that was compiled with "
              "different language options. This is dangerous and therefore not "
              "allowed." );
static_assert( nunavut::support::options::allocator_type == 0,
              "uavcan.node.Mode.1.0"
              "is trying to use a serialization library that was compiled with "
              "different language options. This is dangerous and therefore not "
              "allowed." );
static_assert( nunavut::support::options::allocator_is_default_constructible == 1,
              "uavcan.node.Mode.1.0"
              "is trying to use a serialization library that was compiled with "
              "different language options. This is dangerous and therefore not "
              "allowed." );
static_assert( nunavut::support::options::ctor_convention == 3814588639,
              "uavcan.node.Mode.1.0"
              "is trying to use a serialization library that was compiled with "
              "different language options. This is dangerous and therefore not "
              "allowed." );
static_assert( nunavut::support::options::variant_include == 0,
              "uavcan.node.Mode.1.0"
              "is trying to use a serialization library that was compiled with "
              "different language options. This is dangerous and therefore not "
              "allowed." );


// +-------------------------------------------------------------------------------------------------------------------+
// | This implementation uses the C++17 standard library variant type with wrappers for the emplace and
// | get_if methods to support backwards-compatibility with the C++14 version of this object. The union_value type
// | extends std::variant and can be used with the entire set of variant methods. Using std::variant directly does mean
// | your code will not be backwards compatible with the C++14 version of this object.
// +-------------------------------------------------------------------------------------------------------------------+
///
/// The operating mode of a node.
/// Reserved values can be used in future revisions of the specification.
///
struct Mode_1_0 final
{

    struct _traits_  // The name is surrounded with underscores to avoid collisions with DSDL attributes.
    {
        _traits_() = delete;
        /// This type does not have a fixed port-ID. See https://forum.opencyphal.org/t/choosing-message-and-service-ids/889
        static constexpr bool HasFixedPortID = false;

        static constexpr bool IsServiceType = false;

        static constexpr const char* FullNameAndVersion() { return "uavcan.node.Mode.1.0"; }
    
        /// Extent is the minimum amount of memory required to hold any serialized representation of any compatible
        /// version of the data type; or, on other words, it is the the maximum possible size of received objects of this type.
        /// The size is specified in bytes (rather than bits) because by definition, extent is an integer number of bytes long.
        /// When allocating a deserialization (RX) buffer for this data type, it should be at least extent bytes large.
        /// When allocating a serialization (TX) buffer, it is safe to use the size of the largest serialized representation
        /// instead of the extent because it provides a tighter bound of the object size; it is safe because the concrete type
        /// is always known during serialization (unlike deserialization). If not sure, use extent everywhere.
        static constexpr std::size_t ExtentBytes                  = 1UL;
        static constexpr std::size_t SerializationBufferSizeBytes = 1UL;
        static_assert(ExtentBytes >= SerializationBufferSizeBytes, "Internal constraint violation");
        static_assert(ExtentBytes < (std::numeric_limits<std::size_t>::max() / 8U), "This message is too large to be handled by the selected types");
        struct TypeOf
        {
            TypeOf() = delete;
            using value = std::uint8_t;
        };
    };

    
    // +---------------------------------------------------------------------------------------------------------------+
    // | CONSTANTS
    // +---------------------------------------------------------------------------------------------------------------+
    ///
    /// Normal operating mode.
    ///
    static constexpr std::uint8_t OPERATIONAL = 0U;
    ///
    /// Initialization is in progress; this mode is entered immediately after startup.
    ///
    static constexpr std::uint8_t INITIALIZATION = 1U;
    ///
    /// E.g., calibration, self-test, etc.
    ///
    static constexpr std::uint8_t MAINTENANCE = 2U;
    ///
    /// New software/firmware is being loaded or the bootloader is running.
    ///
    static constexpr std::uint8_t SOFTWARE_UPDATE = 3U;
    
    // +----------------------------------------------------------------------+
    // | FIELDS
    // +----------------------------------------------------------------------+
    
    _traits_::TypeOf::value value{};
};


inline nunavut::support::SerializeResult serialize(const Mode_1_0& obj,
                                                   nunavut::support::bitspan out_buffer)
{
    const std::size_t capacity_bits = out_buffer.size();
    if ((static_cast<std::size_t>(capacity_bits)) < 8UL)
    {
        return -nunavut::support::Error::SerializationBufferTooSmall;
    }
    // Notice that fields that are not an integer number of bytes long may overrun the space allocated for them
    // in the serialization buffer up to the next byte boundary. This is by design and is guaranteed to be safe.
    {   // saturated uint3 value
        std::uint8_t _sat0_ = obj.value;
        if (_sat0_ > 7U)
        {
            _sat0_ = 7U;
        }
        const auto _result3_ = out_buffer.setUxx(_sat0_, 3U);
        if(not _result3_){
            return -_result3_.error();
        }
        out_buffer.add_offset(3U);
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

inline nunavut::support::SerializeResult deserialize(Mode_1_0& obj,
                                                     nunavut::support::const_bitspan in_buffer)
{
    const auto capacity_bits = in_buffer.size();
    // saturated uint3 value
    obj.value = in_buffer.getU8(3U);
    in_buffer.add_offset(3U);
    in_buffer.align_offset_to<8U>();
    auto _bits_got_ = std::min<std::size_t>(in_buffer.offset(), capacity_bits);
    return { static_cast<std::size_t>(_bits_got_ / 8U) };
}

} // namespace node
} // namespace uavcan

#endif // UAVCAN_NODE_MODE_1_0_HPP_INCLUDED
