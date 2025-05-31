//
// This is an AUTO-GENERATED Cyphal DSDL data type implementation. Curious? See https://opencyphal.org.
// You shouldn't attempt to edit this file.
//
// Generator     : nunavut-3.0.0.dev1 (serialization was enabled)
// Source file   : Empty.1.0.dsdl
// Is deprecated : no
// Fixed port-ID : None
// Full name     : uavcan.primitive.Empty
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
#ifndef UAVCAN_PRIMITIVE_EMPTY_1_0_HPP_INCLUDED
#define UAVCAN_PRIMITIVE_EMPTY_1_0_HPP_INCLUDED

#include "nunavut/support/serialization.hpp"
#include <limits>

namespace uavcan
{
namespace primitive
{
// +-------------------------------------------------------------------------------------------------------------------+
// | LANGUAGE OPTION ASSERTIONS
// |    These static assertions ensure that the header is being used with
// | Nunavut C++ serialization support that is compatible with the language
// | options in effect when that support code was generated.
// +-------------------------------------------------------------------------------------------------------------------+
static_assert( nunavut::support::options::target_endianness == 1693710260,
              "uavcan.primitive.Empty.1.0"
              "is trying to use a serialization library that was compiled with "
              "different language options. This is dangerous and therefore not "
              "allowed." );
static_assert( nunavut::support::options::omit_float_serialization_support == 0,
              "uavcan.primitive.Empty.1.0"
              "is trying to use a serialization library that was compiled with "
              "different language options. This is dangerous and therefore not "
              "allowed." );
static_assert( nunavut::support::options::omit_serialization_support == 0,
              "uavcan.primitive.Empty.1.0"
              "is trying to use a serialization library that was compiled with "
              "different language options. This is dangerous and therefore not "
              "allowed." );
static_assert( nunavut::support::options::enable_serialization_asserts == 0,
              "uavcan.primitive.Empty.1.0"
              "is trying to use a serialization library that was compiled with "
              "different language options. This is dangerous and therefore not "
              "allowed." );
static_assert( nunavut::support::options::enable_override_variable_array_capacity == 0,
              "uavcan.primitive.Empty.1.0"
              "is trying to use a serialization library that was compiled with "
              "different language options. This is dangerous and therefore not "
              "allowed." );
static_assert( nunavut::support::options::std == 3161622713,
              "uavcan.primitive.Empty.1.0"
              "is trying to use a serialization library that was compiled with "
              "different language options. This is dangerous and therefore not "
              "allowed." );
static_assert( nunavut::support::options::std_flavor == 2826573480,
              "uavcan.primitive.Empty.1.0"
              "is trying to use a serialization library that was compiled with "
              "different language options. This is dangerous and therefore not "
              "allowed." );
static_assert( nunavut::support::options::cast_format == 1407868567,
              "uavcan.primitive.Empty.1.0"
              "is trying to use a serialization library that was compiled with "
              "different language options. This is dangerous and therefore not "
              "allowed." );
static_assert( nunavut::support::options::variable_array_type_include == 3320664631,
              "uavcan.primitive.Empty.1.0"
              "is trying to use a serialization library that was compiled with "
              "different language options. This is dangerous and therefore not "
              "allowed." );
static_assert( nunavut::support::options::variable_array_type_template == 4227611599,
              "uavcan.primitive.Empty.1.0"
              "is trying to use a serialization library that was compiled with "
              "different language options. This is dangerous and therefore not "
              "allowed." );
static_assert( nunavut::support::options::variable_array_type_constructor_args == 0,
              "uavcan.primitive.Empty.1.0"
              "is trying to use a serialization library that was compiled with "
              "different language options. This is dangerous and therefore not "
              "allowed." );
static_assert( nunavut::support::options::allocator_include == 0,
              "uavcan.primitive.Empty.1.0"
              "is trying to use a serialization library that was compiled with "
              "different language options. This is dangerous and therefore not "
              "allowed." );
static_assert( nunavut::support::options::allocator_type == 0,
              "uavcan.primitive.Empty.1.0"
              "is trying to use a serialization library that was compiled with "
              "different language options. This is dangerous and therefore not "
              "allowed." );
static_assert( nunavut::support::options::allocator_is_default_constructible == 1,
              "uavcan.primitive.Empty.1.0"
              "is trying to use a serialization library that was compiled with "
              "different language options. This is dangerous and therefore not "
              "allowed." );
static_assert( nunavut::support::options::ctor_convention == 3814588639,
              "uavcan.primitive.Empty.1.0"
              "is trying to use a serialization library that was compiled with "
              "different language options. This is dangerous and therefore not "
              "allowed." );
static_assert( nunavut::support::options::variant_include == 0,
              "uavcan.primitive.Empty.1.0"
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

struct Empty_1_0 final
{

    struct _traits_  // The name is surrounded with underscores to avoid collisions with DSDL attributes.
    {
        _traits_() = delete;
        /// This type does not have a fixed port-ID. See https://forum.opencyphal.org/t/choosing-message-and-service-ids/889
        static constexpr bool HasFixedPortID = false;

        static constexpr bool IsServiceType = false;

        static constexpr const char* FullNameAndVersion() { return "uavcan.primitive.Empty.1.0"; }
    
        /// Extent is the minimum amount of memory required to hold any serialized representation of any compatible
        /// version of the data type; or, on other words, it is the the maximum possible size of received objects of this type.
        /// The size is specified in bytes (rather than bits) because by definition, extent is an integer number of bytes long.
        /// When allocating a deserialization (RX) buffer for this data type, it should be at least extent bytes large.
        /// When allocating a serialization (TX) buffer, it is safe to use the size of the largest serialized representation
        /// instead of the extent because it provides a tighter bound of the object size; it is safe because the concrete type
        /// is always known during serialization (unlike deserialization). If not sure, use extent everywhere.
        static constexpr std::size_t ExtentBytes                  = 0UL;
        static constexpr std::size_t SerializationBufferSizeBytes = 0UL;
        static_assert(ExtentBytes >= SerializationBufferSizeBytes, "Internal constraint violation");
        static_assert(ExtentBytes < (std::numeric_limits<std::size_t>::max() / 8U), "This message is too large to be handled by the selected types");
    };

};


inline nunavut::support::SerializeResult serialize(const Empty_1_0& obj,
                                                   nunavut::support::bitspan out_buffer)
{
    (void)(out_buffer);
    (void)(obj);
    return 0U;
}

inline nunavut::support::SerializeResult deserialize(Empty_1_0& obj,
                                                     nunavut::support::const_bitspan in_buffer)
{
    (void)(in_buffer);
    (void)(obj);
    return 0;
}

} // namespace primitive
} // namespace uavcan

#endif // UAVCAN_PRIMITIVE_EMPTY_1_0_HPP_INCLUDED
