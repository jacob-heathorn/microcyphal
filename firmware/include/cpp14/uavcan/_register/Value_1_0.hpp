//
// This is an AUTO-GENERATED Cyphal DSDL data type implementation. Curious? See https://opencyphal.org.
// You shouldn't attempt to edit this file.
//
// Generator     : nunavut-3.0.0.dev1 (serialization was enabled)
// Source file   : Value.1.0.dsdl
// Is deprecated : no
// Fixed port-ID : None
// Full name     : uavcan.register.Value
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
#ifndef UAVCAN_REGISTER_VALUE_1_0_HPP_INCLUDED
#define UAVCAN_REGISTER_VALUE_1_0_HPP_INCLUDED

#include "nunavut/support/serialization.hpp"
#include "uavcan/primitive/Empty_1_0.hpp"
#include "uavcan/primitive/String_1_0.hpp"
#include "uavcan/primitive/Unstructured_1_0.hpp"
#include "uavcan/primitive/array/Bit_1_0.hpp"
#include "uavcan/primitive/array/Integer16_1_0.hpp"
#include "uavcan/primitive/array/Integer32_1_0.hpp"
#include "uavcan/primitive/array/Integer64_1_0.hpp"
#include "uavcan/primitive/array/Integer8_1_0.hpp"
#include "uavcan/primitive/array/Natural16_1_0.hpp"
#include "uavcan/primitive/array/Natural32_1_0.hpp"
#include "uavcan/primitive/array/Natural64_1_0.hpp"
#include "uavcan/primitive/array/Natural8_1_0.hpp"
#include "uavcan/primitive/array/Real16_1_0.hpp"
#include "uavcan/primitive/array/Real32_1_0.hpp"
#include "uavcan/primitive/array/Real64_1_0.hpp"
#include <cstdint>
#include <limits>

namespace uavcan
{
namespace _register
{
// +-------------------------------------------------------------------------------------------------------------------+
// | LANGUAGE OPTION ASSERTIONS
// |    These static assertions ensure that the header is being used with
// | Nunavut C++ serialization support that is compatible with the language
// | options in effect when that support code was generated.
// +-------------------------------------------------------------------------------------------------------------------+
static_assert( nunavut::support::options::target_endianness == 1693710260,
              "uavcan.register.Value.1.0"
              "is trying to use a serialization library that was compiled with "
              "different language options. This is dangerous and therefore not "
              "allowed." );
static_assert( nunavut::support::options::omit_float_serialization_support == 0,
              "uavcan.register.Value.1.0"
              "is trying to use a serialization library that was compiled with "
              "different language options. This is dangerous and therefore not "
              "allowed." );
static_assert( nunavut::support::options::omit_serialization_support == 0,
              "uavcan.register.Value.1.0"
              "is trying to use a serialization library that was compiled with "
              "different language options. This is dangerous and therefore not "
              "allowed." );
static_assert( nunavut::support::options::enable_serialization_asserts == 0,
              "uavcan.register.Value.1.0"
              "is trying to use a serialization library that was compiled with "
              "different language options. This is dangerous and therefore not "
              "allowed." );
static_assert( nunavut::support::options::enable_override_variable_array_capacity == 0,
              "uavcan.register.Value.1.0"
              "is trying to use a serialization library that was compiled with "
              "different language options. This is dangerous and therefore not "
              "allowed." );
static_assert( nunavut::support::options::std == 3161622713,
              "uavcan.register.Value.1.0"
              "is trying to use a serialization library that was compiled with "
              "different language options. This is dangerous and therefore not "
              "allowed." );
static_assert( nunavut::support::options::std_flavor == 2826573480,
              "uavcan.register.Value.1.0"
              "is trying to use a serialization library that was compiled with "
              "different language options. This is dangerous and therefore not "
              "allowed." );
static_assert( nunavut::support::options::cast_format == 1407868567,
              "uavcan.register.Value.1.0"
              "is trying to use a serialization library that was compiled with "
              "different language options. This is dangerous and therefore not "
              "allowed." );
static_assert( nunavut::support::options::variable_array_type_include == 3320664631,
              "uavcan.register.Value.1.0"
              "is trying to use a serialization library that was compiled with "
              "different language options. This is dangerous and therefore not "
              "allowed." );
static_assert( nunavut::support::options::variable_array_type_template == 4227611599,
              "uavcan.register.Value.1.0"
              "is trying to use a serialization library that was compiled with "
              "different language options. This is dangerous and therefore not "
              "allowed." );
static_assert( nunavut::support::options::variable_array_type_constructor_args == 0,
              "uavcan.register.Value.1.0"
              "is trying to use a serialization library that was compiled with "
              "different language options. This is dangerous and therefore not "
              "allowed." );
static_assert( nunavut::support::options::allocator_include == 0,
              "uavcan.register.Value.1.0"
              "is trying to use a serialization library that was compiled with "
              "different language options. This is dangerous and therefore not "
              "allowed." );
static_assert( nunavut::support::options::allocator_type == 0,
              "uavcan.register.Value.1.0"
              "is trying to use a serialization library that was compiled with "
              "different language options. This is dangerous and therefore not "
              "allowed." );
static_assert( nunavut::support::options::allocator_is_default_constructible == 1,
              "uavcan.register.Value.1.0"
              "is trying to use a serialization library that was compiled with "
              "different language options. This is dangerous and therefore not "
              "allowed." );
static_assert( nunavut::support::options::ctor_convention == 3814588639,
              "uavcan.register.Value.1.0"
              "is trying to use a serialization library that was compiled with "
              "different language options. This is dangerous and therefore not "
              "allowed." );
static_assert( nunavut::support::options::variant_include == 0,
              "uavcan.register.Value.1.0"
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
/// This union contains all possible value types supported by the register protocol.
/// Numeric types can be either scalars or arrays; the former is a special case of the latter.
///
struct Value_1_0 final
{

    struct _traits_  // The name is surrounded with underscores to avoid collisions with DSDL attributes.
    {
        _traits_() = delete;
        /// This type does not have a fixed port-ID. See https://forum.opencyphal.org/t/choosing-message-and-service-ids/889
        static constexpr bool HasFixedPortID = false;

        static constexpr bool IsServiceType = false;

        static constexpr const char* FullNameAndVersion() { return "uavcan.register.Value.1.0"; }
    
        /// Extent is the minimum amount of memory required to hold any serialized representation of any compatible
        /// version of the data type; or, on other words, it is the the maximum possible size of received objects of this type.
        /// The size is specified in bytes (rather than bits) because by definition, extent is an integer number of bytes long.
        /// When allocating a deserialization (RX) buffer for this data type, it should be at least extent bytes large.
        /// When allocating a serialization (TX) buffer, it is safe to use the size of the largest serialized representation
        /// instead of the extent because it provides a tighter bound of the object size; it is safe because the concrete type
        /// is always known during serialization (unlike deserialization). If not sure, use extent everywhere.
        static constexpr std::size_t ExtentBytes                  = 259UL;
        static constexpr std::size_t SerializationBufferSizeBytes = 259UL;
        static_assert(ExtentBytes >= SerializationBufferSizeBytes, "Internal constraint violation");
        static_assert(ExtentBytes < (std::numeric_limits<std::size_t>::max() / 8U), "This message is too large to be handled by the selected types");
        struct TypeOf
        {
            TypeOf() = delete;
            using empty = uavcan::primitive::Empty_1_0;
            using string = uavcan::primitive::String_1_0;
            using unstructured = uavcan::primitive::Unstructured_1_0;
            using bit = uavcan::primitive::array::Bit_1_0;
            using integer64 = uavcan::primitive::array::Integer64_1_0;
            using integer32 = uavcan::primitive::array::Integer32_1_0;
            using integer16 = uavcan::primitive::array::Integer16_1_0;
            using integer8 = uavcan::primitive::array::Integer8_1_0;
            using natural64 = uavcan::primitive::array::Natural64_1_0;
            using natural32 = uavcan::primitive::array::Natural32_1_0;
            using natural16 = uavcan::primitive::array::Natural16_1_0;
            using natural8 = uavcan::primitive::array::Natural8_1_0;
            using real64 = uavcan::primitive::array::Real64_1_0;
            using real32 = uavcan::primitive::array::Real32_1_0;
            using real16 = uavcan::primitive::array::Real16_1_0;
        };
    };

    class VariantType final
    {
        std::size_t tag_;

        union internal_union_t
        {
            ///
            /// Tag 0     Used to represent an undefined value
            ///
            std::aligned_storage<sizeof(uavcan::primitive::Empty_1_0), alignof(uavcan::primitive::Empty_1_0)>::type empty;
            ///
            /// Tag 1     UTF-8 encoded text
            ///
            std::aligned_storage<sizeof(uavcan::primitive::String_1_0), alignof(uavcan::primitive::String_1_0)>::type string;
            ///
            /// Tag 2     Raw unstructured binary image
            ///
            std::aligned_storage<sizeof(uavcan::primitive::Unstructured_1_0), alignof(uavcan::primitive::Unstructured_1_0)>::type unstructured;
            ///
            /// Tag 3     Bit array
            ///
            std::aligned_storage<sizeof(uavcan::primitive::array::Bit_1_0), alignof(uavcan::primitive::array::Bit_1_0)>::type bit;
            ///
            /// Tag 4
            ///
            std::aligned_storage<sizeof(uavcan::primitive::array::Integer64_1_0), alignof(uavcan::primitive::array::Integer64_1_0)>::type integer64;
            ///
            /// Tag 5
            ///
            std::aligned_storage<sizeof(uavcan::primitive::array::Integer32_1_0), alignof(uavcan::primitive::array::Integer32_1_0)>::type integer32;
            ///
            /// Tag 6
            ///
            std::aligned_storage<sizeof(uavcan::primitive::array::Integer16_1_0), alignof(uavcan::primitive::array::Integer16_1_0)>::type integer16;
            ///
            /// Tag 7
            ///
            std::aligned_storage<sizeof(uavcan::primitive::array::Integer8_1_0), alignof(uavcan::primitive::array::Integer8_1_0)>::type integer8;
            ///
            /// Tag 8
            ///
            std::aligned_storage<sizeof(uavcan::primitive::array::Natural64_1_0), alignof(uavcan::primitive::array::Natural64_1_0)>::type natural64;
            ///
            /// Tag 9
            ///
            std::aligned_storage<sizeof(uavcan::primitive::array::Natural32_1_0), alignof(uavcan::primitive::array::Natural32_1_0)>::type natural32;
            ///
            /// Tag 10
            ///
            std::aligned_storage<sizeof(uavcan::primitive::array::Natural16_1_0), alignof(uavcan::primitive::array::Natural16_1_0)>::type natural16;
            ///
            /// Tag 11
            ///
            std::aligned_storage<sizeof(uavcan::primitive::array::Natural8_1_0), alignof(uavcan::primitive::array::Natural8_1_0)>::type natural8;
            ///
            /// Tag 12    Exactly representable integers: [-2**53,    +2**53]
            ///
            std::aligned_storage<sizeof(uavcan::primitive::array::Real64_1_0), alignof(uavcan::primitive::array::Real64_1_0)>::type real64;
            ///
            /// Tag 13    Exactly representable integers: [-16777216, +16777216]
            ///
            std::aligned_storage<sizeof(uavcan::primitive::array::Real32_1_0), alignof(uavcan::primitive::array::Real32_1_0)>::type real32;
            ///
            /// Tag 14    Exactly representable integers: [-2048,     +2048]
            ///
            std::aligned_storage<sizeof(uavcan::primitive::array::Real16_1_0), alignof(uavcan::primitive::array::Real16_1_0)>::type real16;
        } internal_union_value_;

    public:
        static const constexpr std::size_t variant_npos = std::numeric_limits<std::size_t>::max();

        VariantType()
            : tag_(0)
            , internal_union_value_()
        {
            // This is how the C++17 standard library does it; default initialization as the 0th index.
            emplace<0>();
        }

        VariantType(const VariantType& rhs)
            : tag_(variant_npos)
            , internal_union_value_()
        {
            if(rhs.tag_ == 0)
            {
                do_copy<0>(
                    *reinterpret_cast<std::add_pointer<const uavcan::primitive::Empty_1_0>::type>(&rhs.internal_union_value_.empty)
                );
            }
            else if(rhs.tag_ == 1)
            {
                do_copy<1>(
                    *reinterpret_cast<std::add_pointer<const uavcan::primitive::String_1_0>::type>(&rhs.internal_union_value_.string)
                );
            }
            else if(rhs.tag_ == 2)
            {
                do_copy<2>(
                    *reinterpret_cast<std::add_pointer<const uavcan::primitive::Unstructured_1_0>::type>(&rhs.internal_union_value_.unstructured)
                );
            }
            else if(rhs.tag_ == 3)
            {
                do_copy<3>(
                    *reinterpret_cast<std::add_pointer<const uavcan::primitive::array::Bit_1_0>::type>(&rhs.internal_union_value_.bit)
                );
            }
            else if(rhs.tag_ == 4)
            {
                do_copy<4>(
                    *reinterpret_cast<std::add_pointer<const uavcan::primitive::array::Integer64_1_0>::type>(&rhs.internal_union_value_.integer64)
                );
            }
            else if(rhs.tag_ == 5)
            {
                do_copy<5>(
                    *reinterpret_cast<std::add_pointer<const uavcan::primitive::array::Integer32_1_0>::type>(&rhs.internal_union_value_.integer32)
                );
            }
            else if(rhs.tag_ == 6)
            {
                do_copy<6>(
                    *reinterpret_cast<std::add_pointer<const uavcan::primitive::array::Integer16_1_0>::type>(&rhs.internal_union_value_.integer16)
                );
            }
            else if(rhs.tag_ == 7)
            {
                do_copy<7>(
                    *reinterpret_cast<std::add_pointer<const uavcan::primitive::array::Integer8_1_0>::type>(&rhs.internal_union_value_.integer8)
                );
            }
            else if(rhs.tag_ == 8)
            {
                do_copy<8>(
                    *reinterpret_cast<std::add_pointer<const uavcan::primitive::array::Natural64_1_0>::type>(&rhs.internal_union_value_.natural64)
                );
            }
            else if(rhs.tag_ == 9)
            {
                do_copy<9>(
                    *reinterpret_cast<std::add_pointer<const uavcan::primitive::array::Natural32_1_0>::type>(&rhs.internal_union_value_.natural32)
                );
            }
            else if(rhs.tag_ == 10)
            {
                do_copy<10>(
                    *reinterpret_cast<std::add_pointer<const uavcan::primitive::array::Natural16_1_0>::type>(&rhs.internal_union_value_.natural16)
                );
            }
            else if(rhs.tag_ == 11)
            {
                do_copy<11>(
                    *reinterpret_cast<std::add_pointer<const uavcan::primitive::array::Natural8_1_0>::type>(&rhs.internal_union_value_.natural8)
                );
            }
            else if(rhs.tag_ == 12)
            {
                do_copy<12>(
                    *reinterpret_cast<std::add_pointer<const uavcan::primitive::array::Real64_1_0>::type>(&rhs.internal_union_value_.real64)
                );
            }
            else if(rhs.tag_ == 13)
            {
                do_copy<13>(
                    *reinterpret_cast<std::add_pointer<const uavcan::primitive::array::Real32_1_0>::type>(&rhs.internal_union_value_.real32)
                );
            }
            else if(rhs.tag_ == 14)
            {
                do_copy<14>(
                    *reinterpret_cast<std::add_pointer<const uavcan::primitive::array::Real16_1_0>::type>(&rhs.internal_union_value_.real16)
                );
            }
            tag_ = rhs.tag_;
        }

        VariantType(VariantType&& rhs)
            : tag_(variant_npos)
            , internal_union_value_()
        {
            if(rhs.tag_ == 0)
            {
                do_emplace<0>(
                    std::forward<uavcan::primitive::Empty_1_0>(
                        *reinterpret_cast<std::add_pointer<uavcan::primitive::Empty_1_0>::type>(&rhs.internal_union_value_.empty)
                    )
                );
            }
            else if(rhs.tag_ == 1)
            {
                do_emplace<1>(
                    std::forward<uavcan::primitive::String_1_0>(
                        *reinterpret_cast<std::add_pointer<uavcan::primitive::String_1_0>::type>(&rhs.internal_union_value_.string)
                    )
                );
            }
            else if(rhs.tag_ == 2)
            {
                do_emplace<2>(
                    std::forward<uavcan::primitive::Unstructured_1_0>(
                        *reinterpret_cast<std::add_pointer<uavcan::primitive::Unstructured_1_0>::type>(&rhs.internal_union_value_.unstructured)
                    )
                );
            }
            else if(rhs.tag_ == 3)
            {
                do_emplace<3>(
                    std::forward<uavcan::primitive::array::Bit_1_0>(
                        *reinterpret_cast<std::add_pointer<uavcan::primitive::array::Bit_1_0>::type>(&rhs.internal_union_value_.bit)
                    )
                );
            }
            else if(rhs.tag_ == 4)
            {
                do_emplace<4>(
                    std::forward<uavcan::primitive::array::Integer64_1_0>(
                        *reinterpret_cast<std::add_pointer<uavcan::primitive::array::Integer64_1_0>::type>(&rhs.internal_union_value_.integer64)
                    )
                );
            }
            else if(rhs.tag_ == 5)
            {
                do_emplace<5>(
                    std::forward<uavcan::primitive::array::Integer32_1_0>(
                        *reinterpret_cast<std::add_pointer<uavcan::primitive::array::Integer32_1_0>::type>(&rhs.internal_union_value_.integer32)
                    )
                );
            }
            else if(rhs.tag_ == 6)
            {
                do_emplace<6>(
                    std::forward<uavcan::primitive::array::Integer16_1_0>(
                        *reinterpret_cast<std::add_pointer<uavcan::primitive::array::Integer16_1_0>::type>(&rhs.internal_union_value_.integer16)
                    )
                );
            }
            else if(rhs.tag_ == 7)
            {
                do_emplace<7>(
                    std::forward<uavcan::primitive::array::Integer8_1_0>(
                        *reinterpret_cast<std::add_pointer<uavcan::primitive::array::Integer8_1_0>::type>(&rhs.internal_union_value_.integer8)
                    )
                );
            }
            else if(rhs.tag_ == 8)
            {
                do_emplace<8>(
                    std::forward<uavcan::primitive::array::Natural64_1_0>(
                        *reinterpret_cast<std::add_pointer<uavcan::primitive::array::Natural64_1_0>::type>(&rhs.internal_union_value_.natural64)
                    )
                );
            }
            else if(rhs.tag_ == 9)
            {
                do_emplace<9>(
                    std::forward<uavcan::primitive::array::Natural32_1_0>(
                        *reinterpret_cast<std::add_pointer<uavcan::primitive::array::Natural32_1_0>::type>(&rhs.internal_union_value_.natural32)
                    )
                );
            }
            else if(rhs.tag_ == 10)
            {
                do_emplace<10>(
                    std::forward<uavcan::primitive::array::Natural16_1_0>(
                        *reinterpret_cast<std::add_pointer<uavcan::primitive::array::Natural16_1_0>::type>(&rhs.internal_union_value_.natural16)
                    )
                );
            }
            else if(rhs.tag_ == 11)
            {
                do_emplace<11>(
                    std::forward<uavcan::primitive::array::Natural8_1_0>(
                        *reinterpret_cast<std::add_pointer<uavcan::primitive::array::Natural8_1_0>::type>(&rhs.internal_union_value_.natural8)
                    )
                );
            }
            else if(rhs.tag_ == 12)
            {
                do_emplace<12>(
                    std::forward<uavcan::primitive::array::Real64_1_0>(
                        *reinterpret_cast<std::add_pointer<uavcan::primitive::array::Real64_1_0>::type>(&rhs.internal_union_value_.real64)
                    )
                );
            }
            else if(rhs.tag_ == 13)
            {
                do_emplace<13>(
                    std::forward<uavcan::primitive::array::Real32_1_0>(
                        *reinterpret_cast<std::add_pointer<uavcan::primitive::array::Real32_1_0>::type>(&rhs.internal_union_value_.real32)
                    )
                );
            }
            else if(rhs.tag_ == 14)
            {
                do_emplace<14>(
                    std::forward<uavcan::primitive::array::Real16_1_0>(
                        *reinterpret_cast<std::add_pointer<uavcan::primitive::array::Real16_1_0>::type>(&rhs.internal_union_value_.real16)
                    )
                );
            }
            tag_ = rhs.tag_;
        }
        VariantType& operator=(const VariantType& rhs)
        {
            destroy_current();
            if(rhs.tag_ == 0)
            {
                do_copy<0>(
                    *reinterpret_cast<std::add_pointer<const uavcan::primitive::Empty_1_0>::type>(&rhs.internal_union_value_.empty)
                );
            }
            else if(rhs.tag_ == 1)
            {
                do_copy<1>(
                    *reinterpret_cast<std::add_pointer<const uavcan::primitive::String_1_0>::type>(&rhs.internal_union_value_.string)
                );
            }
            else if(rhs.tag_ == 2)
            {
                do_copy<2>(
                    *reinterpret_cast<std::add_pointer<const uavcan::primitive::Unstructured_1_0>::type>(&rhs.internal_union_value_.unstructured)
                );
            }
            else if(rhs.tag_ == 3)
            {
                do_copy<3>(
                    *reinterpret_cast<std::add_pointer<const uavcan::primitive::array::Bit_1_0>::type>(&rhs.internal_union_value_.bit)
                );
            }
            else if(rhs.tag_ == 4)
            {
                do_copy<4>(
                    *reinterpret_cast<std::add_pointer<const uavcan::primitive::array::Integer64_1_0>::type>(&rhs.internal_union_value_.integer64)
                );
            }
            else if(rhs.tag_ == 5)
            {
                do_copy<5>(
                    *reinterpret_cast<std::add_pointer<const uavcan::primitive::array::Integer32_1_0>::type>(&rhs.internal_union_value_.integer32)
                );
            }
            else if(rhs.tag_ == 6)
            {
                do_copy<6>(
                    *reinterpret_cast<std::add_pointer<const uavcan::primitive::array::Integer16_1_0>::type>(&rhs.internal_union_value_.integer16)
                );
            }
            else if(rhs.tag_ == 7)
            {
                do_copy<7>(
                    *reinterpret_cast<std::add_pointer<const uavcan::primitive::array::Integer8_1_0>::type>(&rhs.internal_union_value_.integer8)
                );
            }
            else if(rhs.tag_ == 8)
            {
                do_copy<8>(
                    *reinterpret_cast<std::add_pointer<const uavcan::primitive::array::Natural64_1_0>::type>(&rhs.internal_union_value_.natural64)
                );
            }
            else if(rhs.tag_ == 9)
            {
                do_copy<9>(
                    *reinterpret_cast<std::add_pointer<const uavcan::primitive::array::Natural32_1_0>::type>(&rhs.internal_union_value_.natural32)
                );
            }
            else if(rhs.tag_ == 10)
            {
                do_copy<10>(
                    *reinterpret_cast<std::add_pointer<const uavcan::primitive::array::Natural16_1_0>::type>(&rhs.internal_union_value_.natural16)
                );
            }
            else if(rhs.tag_ == 11)
            {
                do_copy<11>(
                    *reinterpret_cast<std::add_pointer<const uavcan::primitive::array::Natural8_1_0>::type>(&rhs.internal_union_value_.natural8)
                );
            }
            else if(rhs.tag_ == 12)
            {
                do_copy<12>(
                    *reinterpret_cast<std::add_pointer<const uavcan::primitive::array::Real64_1_0>::type>(&rhs.internal_union_value_.real64)
                );
            }
            else if(rhs.tag_ == 13)
            {
                do_copy<13>(
                    *reinterpret_cast<std::add_pointer<const uavcan::primitive::array::Real32_1_0>::type>(&rhs.internal_union_value_.real32)
                );
            }
            else if(rhs.tag_ == 14)
            {
                do_copy<14>(
                    *reinterpret_cast<std::add_pointer<const uavcan::primitive::array::Real16_1_0>::type>(&rhs.internal_union_value_.real16)
                );
            }
            tag_ = rhs.tag_;
            return *this;
        }

        VariantType& operator=(VariantType&& rhs)
        {
            destroy_current();
            if(rhs.tag_ == 0)
            {
                do_emplace<0>(
                    std::forward<uavcan::primitive::Empty_1_0>(
                        *reinterpret_cast<std::add_pointer<uavcan::primitive::Empty_1_0>::type>(&rhs.internal_union_value_.empty)
                    )
                );
            }
            else if(rhs.tag_ == 1)
            {
                do_emplace<1>(
                    std::forward<uavcan::primitive::String_1_0>(
                        *reinterpret_cast<std::add_pointer<uavcan::primitive::String_1_0>::type>(&rhs.internal_union_value_.string)
                    )
                );
            }
            else if(rhs.tag_ == 2)
            {
                do_emplace<2>(
                    std::forward<uavcan::primitive::Unstructured_1_0>(
                        *reinterpret_cast<std::add_pointer<uavcan::primitive::Unstructured_1_0>::type>(&rhs.internal_union_value_.unstructured)
                    )
                );
            }
            else if(rhs.tag_ == 3)
            {
                do_emplace<3>(
                    std::forward<uavcan::primitive::array::Bit_1_0>(
                        *reinterpret_cast<std::add_pointer<uavcan::primitive::array::Bit_1_0>::type>(&rhs.internal_union_value_.bit)
                    )
                );
            }
            else if(rhs.tag_ == 4)
            {
                do_emplace<4>(
                    std::forward<uavcan::primitive::array::Integer64_1_0>(
                        *reinterpret_cast<std::add_pointer<uavcan::primitive::array::Integer64_1_0>::type>(&rhs.internal_union_value_.integer64)
                    )
                );
            }
            else if(rhs.tag_ == 5)
            {
                do_emplace<5>(
                    std::forward<uavcan::primitive::array::Integer32_1_0>(
                        *reinterpret_cast<std::add_pointer<uavcan::primitive::array::Integer32_1_0>::type>(&rhs.internal_union_value_.integer32)
                    )
                );
            }
            else if(rhs.tag_ == 6)
            {
                do_emplace<6>(
                    std::forward<uavcan::primitive::array::Integer16_1_0>(
                        *reinterpret_cast<std::add_pointer<uavcan::primitive::array::Integer16_1_0>::type>(&rhs.internal_union_value_.integer16)
                    )
                );
            }
            else if(rhs.tag_ == 7)
            {
                do_emplace<7>(
                    std::forward<uavcan::primitive::array::Integer8_1_0>(
                        *reinterpret_cast<std::add_pointer<uavcan::primitive::array::Integer8_1_0>::type>(&rhs.internal_union_value_.integer8)
                    )
                );
            }
            else if(rhs.tag_ == 8)
            {
                do_emplace<8>(
                    std::forward<uavcan::primitive::array::Natural64_1_0>(
                        *reinterpret_cast<std::add_pointer<uavcan::primitive::array::Natural64_1_0>::type>(&rhs.internal_union_value_.natural64)
                    )
                );
            }
            else if(rhs.tag_ == 9)
            {
                do_emplace<9>(
                    std::forward<uavcan::primitive::array::Natural32_1_0>(
                        *reinterpret_cast<std::add_pointer<uavcan::primitive::array::Natural32_1_0>::type>(&rhs.internal_union_value_.natural32)
                    )
                );
            }
            else if(rhs.tag_ == 10)
            {
                do_emplace<10>(
                    std::forward<uavcan::primitive::array::Natural16_1_0>(
                        *reinterpret_cast<std::add_pointer<uavcan::primitive::array::Natural16_1_0>::type>(&rhs.internal_union_value_.natural16)
                    )
                );
            }
            else if(rhs.tag_ == 11)
            {
                do_emplace<11>(
                    std::forward<uavcan::primitive::array::Natural8_1_0>(
                        *reinterpret_cast<std::add_pointer<uavcan::primitive::array::Natural8_1_0>::type>(&rhs.internal_union_value_.natural8)
                    )
                );
            }
            else if(rhs.tag_ == 12)
            {
                do_emplace<12>(
                    std::forward<uavcan::primitive::array::Real64_1_0>(
                        *reinterpret_cast<std::add_pointer<uavcan::primitive::array::Real64_1_0>::type>(&rhs.internal_union_value_.real64)
                    )
                );
            }
            else if(rhs.tag_ == 13)
            {
                do_emplace<13>(
                    std::forward<uavcan::primitive::array::Real32_1_0>(
                        *reinterpret_cast<std::add_pointer<uavcan::primitive::array::Real32_1_0>::type>(&rhs.internal_union_value_.real32)
                    )
                );
            }
            else if(rhs.tag_ == 14)
            {
                do_emplace<14>(
                    std::forward<uavcan::primitive::array::Real16_1_0>(
                        *reinterpret_cast<std::add_pointer<uavcan::primitive::array::Real16_1_0>::type>(&rhs.internal_union_value_.real16)
                    )
                );
            }
            tag_ = rhs.tag_;
            return *this;
        }

        ~VariantType()
        {
            destroy_current();
        }

        size_t index() const{
            return tag_;
        }

        struct IndexOf final
        {
            IndexOf() = delete;
            static constexpr const std::size_t empty = 0U;
            static constexpr const std::size_t string = 1U;
            static constexpr const std::size_t unstructured = 2U;
            static constexpr const std::size_t bit = 3U;
            static constexpr const std::size_t integer64 = 4U;
            static constexpr const std::size_t integer32 = 5U;
            static constexpr const std::size_t integer16 = 6U;
            static constexpr const std::size_t integer8 = 7U;
            static constexpr const std::size_t natural64 = 8U;
            static constexpr const std::size_t natural32 = 9U;
            static constexpr const std::size_t natural16 = 10U;
            static constexpr const std::size_t natural8 = 11U;
            static constexpr const std::size_t real64 = 12U;
            static constexpr const std::size_t real32 = 13U;
            static constexpr const std::size_t real16 = 14U;
        };
        static constexpr const std::size_t MAX_INDEX = 15U;

        template<std::size_t I, class...Types> struct alternative;


        template<class...Types> struct alternative<0U, Types...>
        {
            using type = uavcan::primitive::Empty_1_0;
            static constexpr auto pointer = &VariantType::internal_union_t::empty;
        };
        template<class...Types> struct alternative<1U, Types...>
        {
            using type = uavcan::primitive::String_1_0;
            static constexpr auto pointer = &VariantType::internal_union_t::string;
        };
        template<class...Types> struct alternative<2U, Types...>
        {
            using type = uavcan::primitive::Unstructured_1_0;
            static constexpr auto pointer = &VariantType::internal_union_t::unstructured;
        };
        template<class...Types> struct alternative<3U, Types...>
        {
            using type = uavcan::primitive::array::Bit_1_0;
            static constexpr auto pointer = &VariantType::internal_union_t::bit;
        };
        template<class...Types> struct alternative<4U, Types...>
        {
            using type = uavcan::primitive::array::Integer64_1_0;
            static constexpr auto pointer = &VariantType::internal_union_t::integer64;
        };
        template<class...Types> struct alternative<5U, Types...>
        {
            using type = uavcan::primitive::array::Integer32_1_0;
            static constexpr auto pointer = &VariantType::internal_union_t::integer32;
        };
        template<class...Types> struct alternative<6U, Types...>
        {
            using type = uavcan::primitive::array::Integer16_1_0;
            static constexpr auto pointer = &VariantType::internal_union_t::integer16;
        };
        template<class...Types> struct alternative<7U, Types...>
        {
            using type = uavcan::primitive::array::Integer8_1_0;
            static constexpr auto pointer = &VariantType::internal_union_t::integer8;
        };
        template<class...Types> struct alternative<8U, Types...>
        {
            using type = uavcan::primitive::array::Natural64_1_0;
            static constexpr auto pointer = &VariantType::internal_union_t::natural64;
        };
        template<class...Types> struct alternative<9U, Types...>
        {
            using type = uavcan::primitive::array::Natural32_1_0;
            static constexpr auto pointer = &VariantType::internal_union_t::natural32;
        };
        template<class...Types> struct alternative<10U, Types...>
        {
            using type = uavcan::primitive::array::Natural16_1_0;
            static constexpr auto pointer = &VariantType::internal_union_t::natural16;
        };
        template<class...Types> struct alternative<11U, Types...>
        {
            using type = uavcan::primitive::array::Natural8_1_0;
            static constexpr auto pointer = &VariantType::internal_union_t::natural8;
        };
        template<class...Types> struct alternative<12U, Types...>
        {
            using type = uavcan::primitive::array::Real64_1_0;
            static constexpr auto pointer = &VariantType::internal_union_t::real64;
        };
        template<class...Types> struct alternative<13U, Types...>
        {
            using type = uavcan::primitive::array::Real32_1_0;
            static constexpr auto pointer = &VariantType::internal_union_t::real32;
        };
        template<class...Types> struct alternative<14U, Types...>
        {
            using type = uavcan::primitive::array::Real16_1_0;
            static constexpr auto pointer = &VariantType::internal_union_t::real16;
        };

        template<std::size_t I, class... Args> typename VariantType::alternative<I, VariantType>::type& emplace(Args&&... v)
        {
            destroy_current();
            typename alternative<I>::type& result = do_emplace<I>(v...);
            tag_ = I;
            return result;
        }

        template<std::size_t I, class... Types>
        static constexpr typename alternative<I, VariantType>::type* get_if(VariantType* v) noexcept
        {
            return (v) ? v->do_get_if<I>() : nullptr;
        }

        template<std::size_t I, class... Types>
        static constexpr const typename alternative<I, VariantType>::type* get_if(const VariantType* v) noexcept
        {
            return (v) ? v->do_get_if_const<I>() : nullptr;
        }

    private:
        template<std::size_t I, class... Args> typename VariantType::alternative<I, VariantType>::type& do_emplace(Args&&... v)
        {
            return *(new (&(internal_union_value_.*(alternative<I>::pointer)) ) typename alternative<I>::type(std::forward<Args>(v)...));
        }

        template<std::size_t I, class... Args> typename VariantType::alternative<I, VariantType>::type& do_copy(const Args&... v)
        {
            return *(new (&(internal_union_value_.*(alternative<I>::pointer)) ) typename alternative<I>::type(typename alternative<I>::type(v...)));
        }

        template<std::size_t I, class... Types>
        constexpr typename VariantType::alternative<I, VariantType>::type* do_get_if() noexcept
        {
            return (tag_ == I) ? reinterpret_cast<typename std::add_pointer<typename VariantType::alternative<I>::type>::type>(&(internal_union_value_.*(alternative<I>::pointer))) : nullptr;
        }

        template<std::size_t I, class... Types>
        constexpr const typename VariantType::alternative<I, VariantType>::type* do_get_if_const() const noexcept
        {
            return (tag_ == I) ? reinterpret_cast<typename std::add_pointer<const typename VariantType::alternative<I>::type>::type>(&(internal_union_value_.*(alternative<I>::pointer))) : nullptr;
        }

        void destroy_current()
        {
            if (tag_ == 0)
            {
                reinterpret_cast<uavcan::primitive::Empty_1_0*>(std::addressof(internal_union_value_.empty))->~Empty_1_0();
            }
            else if (tag_ == 1)
            {
                reinterpret_cast<uavcan::primitive::String_1_0*>(std::addressof(internal_union_value_.string))->~String_1_0();
            }
            else if (tag_ == 2)
            {
                reinterpret_cast<uavcan::primitive::Unstructured_1_0*>(std::addressof(internal_union_value_.unstructured))->~Unstructured_1_0();
            }
            else if (tag_ == 3)
            {
                reinterpret_cast<uavcan::primitive::array::Bit_1_0*>(std::addressof(internal_union_value_.bit))->~Bit_1_0();
            }
            else if (tag_ == 4)
            {
                reinterpret_cast<uavcan::primitive::array::Integer64_1_0*>(std::addressof(internal_union_value_.integer64))->~Integer64_1_0();
            }
            else if (tag_ == 5)
            {
                reinterpret_cast<uavcan::primitive::array::Integer32_1_0*>(std::addressof(internal_union_value_.integer32))->~Integer32_1_0();
            }
            else if (tag_ == 6)
            {
                reinterpret_cast<uavcan::primitive::array::Integer16_1_0*>(std::addressof(internal_union_value_.integer16))->~Integer16_1_0();
            }
            else if (tag_ == 7)
            {
                reinterpret_cast<uavcan::primitive::array::Integer8_1_0*>(std::addressof(internal_union_value_.integer8))->~Integer8_1_0();
            }
            else if (tag_ == 8)
            {
                reinterpret_cast<uavcan::primitive::array::Natural64_1_0*>(std::addressof(internal_union_value_.natural64))->~Natural64_1_0();
            }
            else if (tag_ == 9)
            {
                reinterpret_cast<uavcan::primitive::array::Natural32_1_0*>(std::addressof(internal_union_value_.natural32))->~Natural32_1_0();
            }
            else if (tag_ == 10)
            {
                reinterpret_cast<uavcan::primitive::array::Natural16_1_0*>(std::addressof(internal_union_value_.natural16))->~Natural16_1_0();
            }
            else if (tag_ == 11)
            {
                reinterpret_cast<uavcan::primitive::array::Natural8_1_0*>(std::addressof(internal_union_value_.natural8))->~Natural8_1_0();
            }
            else if (tag_ == 12)
            {
                reinterpret_cast<uavcan::primitive::array::Real64_1_0*>(std::addressof(internal_union_value_.real64))->~Real64_1_0();
            }
            else if (tag_ == 13)
            {
                reinterpret_cast<uavcan::primitive::array::Real32_1_0*>(std::addressof(internal_union_value_.real32))->~Real32_1_0();
            }
            else if (tag_ == 14)
            {
                reinterpret_cast<uavcan::primitive::array::Real16_1_0*>(std::addressof(internal_union_value_.real16))->~Real16_1_0();
            }
        }

    };

    VariantType union_value;


    bool is_empty() const
    {
        return VariantType::IndexOf::empty == union_value.index();
    }
    typename std::add_pointer<_traits_::TypeOf::empty>::type get_empty_if()
    {
        return VariantType::get_if<VariantType::IndexOf::empty>(&union_value);
    }
    typename std::add_pointer<const _traits_::TypeOf::empty>::type get_empty_if() const
    {
        return VariantType::get_if<VariantType::IndexOf::empty>(&union_value);
    }
    typename std::add_lvalue_reference<_traits_::TypeOf::empty>::type get_empty()
    {
        
        return *VariantType::get_if<VariantType::IndexOf::empty>(&union_value);
    }
    typename std::add_lvalue_reference<const _traits_::TypeOf::empty>::type get_empty() const
    {
        
        return *VariantType::get_if<VariantType::IndexOf::empty>(&union_value);
    }
    template<class... Args> typename std::add_lvalue_reference<_traits_::TypeOf::empty>::type
    set_empty(Args&&...v)
    {
        return union_value.emplace<VariantType::IndexOf::empty>(v...);
    }

    bool is_string() const
    {
        return VariantType::IndexOf::string == union_value.index();
    }
    typename std::add_pointer<_traits_::TypeOf::string>::type get_string_if()
    {
        return VariantType::get_if<VariantType::IndexOf::string>(&union_value);
    }
    typename std::add_pointer<const _traits_::TypeOf::string>::type get_string_if() const
    {
        return VariantType::get_if<VariantType::IndexOf::string>(&union_value);
    }
    typename std::add_lvalue_reference<_traits_::TypeOf::string>::type get_string()
    {
        
        return *VariantType::get_if<VariantType::IndexOf::string>(&union_value);
    }
    typename std::add_lvalue_reference<const _traits_::TypeOf::string>::type get_string() const
    {
        
        return *VariantType::get_if<VariantType::IndexOf::string>(&union_value);
    }
    template<class... Args> typename std::add_lvalue_reference<_traits_::TypeOf::string>::type
    set_string(Args&&...v)
    {
        return union_value.emplace<VariantType::IndexOf::string>(v...);
    }

    bool is_unstructured() const
    {
        return VariantType::IndexOf::unstructured == union_value.index();
    }
    typename std::add_pointer<_traits_::TypeOf::unstructured>::type get_unstructured_if()
    {
        return VariantType::get_if<VariantType::IndexOf::unstructured>(&union_value);
    }
    typename std::add_pointer<const _traits_::TypeOf::unstructured>::type get_unstructured_if() const
    {
        return VariantType::get_if<VariantType::IndexOf::unstructured>(&union_value);
    }
    typename std::add_lvalue_reference<_traits_::TypeOf::unstructured>::type get_unstructured()
    {
        
        return *VariantType::get_if<VariantType::IndexOf::unstructured>(&union_value);
    }
    typename std::add_lvalue_reference<const _traits_::TypeOf::unstructured>::type get_unstructured() const
    {
        
        return *VariantType::get_if<VariantType::IndexOf::unstructured>(&union_value);
    }
    template<class... Args> typename std::add_lvalue_reference<_traits_::TypeOf::unstructured>::type
    set_unstructured(Args&&...v)
    {
        return union_value.emplace<VariantType::IndexOf::unstructured>(v...);
    }

    bool is_bit() const
    {
        return VariantType::IndexOf::bit == union_value.index();
    }
    typename std::add_pointer<_traits_::TypeOf::bit>::type get_bit_if()
    {
        return VariantType::get_if<VariantType::IndexOf::bit>(&union_value);
    }
    typename std::add_pointer<const _traits_::TypeOf::bit>::type get_bit_if() const
    {
        return VariantType::get_if<VariantType::IndexOf::bit>(&union_value);
    }
    typename std::add_lvalue_reference<_traits_::TypeOf::bit>::type get_bit()
    {
        
        return *VariantType::get_if<VariantType::IndexOf::bit>(&union_value);
    }
    typename std::add_lvalue_reference<const _traits_::TypeOf::bit>::type get_bit() const
    {
        
        return *VariantType::get_if<VariantType::IndexOf::bit>(&union_value);
    }
    template<class... Args> typename std::add_lvalue_reference<_traits_::TypeOf::bit>::type
    set_bit(Args&&...v)
    {
        return union_value.emplace<VariantType::IndexOf::bit>(v...);
    }

    bool is_integer64() const
    {
        return VariantType::IndexOf::integer64 == union_value.index();
    }
    typename std::add_pointer<_traits_::TypeOf::integer64>::type get_integer64_if()
    {
        return VariantType::get_if<VariantType::IndexOf::integer64>(&union_value);
    }
    typename std::add_pointer<const _traits_::TypeOf::integer64>::type get_integer64_if() const
    {
        return VariantType::get_if<VariantType::IndexOf::integer64>(&union_value);
    }
    typename std::add_lvalue_reference<_traits_::TypeOf::integer64>::type get_integer64()
    {
        
        return *VariantType::get_if<VariantType::IndexOf::integer64>(&union_value);
    }
    typename std::add_lvalue_reference<const _traits_::TypeOf::integer64>::type get_integer64() const
    {
        
        return *VariantType::get_if<VariantType::IndexOf::integer64>(&union_value);
    }
    template<class... Args> typename std::add_lvalue_reference<_traits_::TypeOf::integer64>::type
    set_integer64(Args&&...v)
    {
        return union_value.emplace<VariantType::IndexOf::integer64>(v...);
    }

    bool is_integer32() const
    {
        return VariantType::IndexOf::integer32 == union_value.index();
    }
    typename std::add_pointer<_traits_::TypeOf::integer32>::type get_integer32_if()
    {
        return VariantType::get_if<VariantType::IndexOf::integer32>(&union_value);
    }
    typename std::add_pointer<const _traits_::TypeOf::integer32>::type get_integer32_if() const
    {
        return VariantType::get_if<VariantType::IndexOf::integer32>(&union_value);
    }
    typename std::add_lvalue_reference<_traits_::TypeOf::integer32>::type get_integer32()
    {
        
        return *VariantType::get_if<VariantType::IndexOf::integer32>(&union_value);
    }
    typename std::add_lvalue_reference<const _traits_::TypeOf::integer32>::type get_integer32() const
    {
        
        return *VariantType::get_if<VariantType::IndexOf::integer32>(&union_value);
    }
    template<class... Args> typename std::add_lvalue_reference<_traits_::TypeOf::integer32>::type
    set_integer32(Args&&...v)
    {
        return union_value.emplace<VariantType::IndexOf::integer32>(v...);
    }

    bool is_integer16() const
    {
        return VariantType::IndexOf::integer16 == union_value.index();
    }
    typename std::add_pointer<_traits_::TypeOf::integer16>::type get_integer16_if()
    {
        return VariantType::get_if<VariantType::IndexOf::integer16>(&union_value);
    }
    typename std::add_pointer<const _traits_::TypeOf::integer16>::type get_integer16_if() const
    {
        return VariantType::get_if<VariantType::IndexOf::integer16>(&union_value);
    }
    typename std::add_lvalue_reference<_traits_::TypeOf::integer16>::type get_integer16()
    {
        
        return *VariantType::get_if<VariantType::IndexOf::integer16>(&union_value);
    }
    typename std::add_lvalue_reference<const _traits_::TypeOf::integer16>::type get_integer16() const
    {
        
        return *VariantType::get_if<VariantType::IndexOf::integer16>(&union_value);
    }
    template<class... Args> typename std::add_lvalue_reference<_traits_::TypeOf::integer16>::type
    set_integer16(Args&&...v)
    {
        return union_value.emplace<VariantType::IndexOf::integer16>(v...);
    }

    bool is_integer8() const
    {
        return VariantType::IndexOf::integer8 == union_value.index();
    }
    typename std::add_pointer<_traits_::TypeOf::integer8>::type get_integer8_if()
    {
        return VariantType::get_if<VariantType::IndexOf::integer8>(&union_value);
    }
    typename std::add_pointer<const _traits_::TypeOf::integer8>::type get_integer8_if() const
    {
        return VariantType::get_if<VariantType::IndexOf::integer8>(&union_value);
    }
    typename std::add_lvalue_reference<_traits_::TypeOf::integer8>::type get_integer8()
    {
        
        return *VariantType::get_if<VariantType::IndexOf::integer8>(&union_value);
    }
    typename std::add_lvalue_reference<const _traits_::TypeOf::integer8>::type get_integer8() const
    {
        
        return *VariantType::get_if<VariantType::IndexOf::integer8>(&union_value);
    }
    template<class... Args> typename std::add_lvalue_reference<_traits_::TypeOf::integer8>::type
    set_integer8(Args&&...v)
    {
        return union_value.emplace<VariantType::IndexOf::integer8>(v...);
    }

    bool is_natural64() const
    {
        return VariantType::IndexOf::natural64 == union_value.index();
    }
    typename std::add_pointer<_traits_::TypeOf::natural64>::type get_natural64_if()
    {
        return VariantType::get_if<VariantType::IndexOf::natural64>(&union_value);
    }
    typename std::add_pointer<const _traits_::TypeOf::natural64>::type get_natural64_if() const
    {
        return VariantType::get_if<VariantType::IndexOf::natural64>(&union_value);
    }
    typename std::add_lvalue_reference<_traits_::TypeOf::natural64>::type get_natural64()
    {
        
        return *VariantType::get_if<VariantType::IndexOf::natural64>(&union_value);
    }
    typename std::add_lvalue_reference<const _traits_::TypeOf::natural64>::type get_natural64() const
    {
        
        return *VariantType::get_if<VariantType::IndexOf::natural64>(&union_value);
    }
    template<class... Args> typename std::add_lvalue_reference<_traits_::TypeOf::natural64>::type
    set_natural64(Args&&...v)
    {
        return union_value.emplace<VariantType::IndexOf::natural64>(v...);
    }

    bool is_natural32() const
    {
        return VariantType::IndexOf::natural32 == union_value.index();
    }
    typename std::add_pointer<_traits_::TypeOf::natural32>::type get_natural32_if()
    {
        return VariantType::get_if<VariantType::IndexOf::natural32>(&union_value);
    }
    typename std::add_pointer<const _traits_::TypeOf::natural32>::type get_natural32_if() const
    {
        return VariantType::get_if<VariantType::IndexOf::natural32>(&union_value);
    }
    typename std::add_lvalue_reference<_traits_::TypeOf::natural32>::type get_natural32()
    {
        
        return *VariantType::get_if<VariantType::IndexOf::natural32>(&union_value);
    }
    typename std::add_lvalue_reference<const _traits_::TypeOf::natural32>::type get_natural32() const
    {
        
        return *VariantType::get_if<VariantType::IndexOf::natural32>(&union_value);
    }
    template<class... Args> typename std::add_lvalue_reference<_traits_::TypeOf::natural32>::type
    set_natural32(Args&&...v)
    {
        return union_value.emplace<VariantType::IndexOf::natural32>(v...);
    }

    bool is_natural16() const
    {
        return VariantType::IndexOf::natural16 == union_value.index();
    }
    typename std::add_pointer<_traits_::TypeOf::natural16>::type get_natural16_if()
    {
        return VariantType::get_if<VariantType::IndexOf::natural16>(&union_value);
    }
    typename std::add_pointer<const _traits_::TypeOf::natural16>::type get_natural16_if() const
    {
        return VariantType::get_if<VariantType::IndexOf::natural16>(&union_value);
    }
    typename std::add_lvalue_reference<_traits_::TypeOf::natural16>::type get_natural16()
    {
        
        return *VariantType::get_if<VariantType::IndexOf::natural16>(&union_value);
    }
    typename std::add_lvalue_reference<const _traits_::TypeOf::natural16>::type get_natural16() const
    {
        
        return *VariantType::get_if<VariantType::IndexOf::natural16>(&union_value);
    }
    template<class... Args> typename std::add_lvalue_reference<_traits_::TypeOf::natural16>::type
    set_natural16(Args&&...v)
    {
        return union_value.emplace<VariantType::IndexOf::natural16>(v...);
    }

    bool is_natural8() const
    {
        return VariantType::IndexOf::natural8 == union_value.index();
    }
    typename std::add_pointer<_traits_::TypeOf::natural8>::type get_natural8_if()
    {
        return VariantType::get_if<VariantType::IndexOf::natural8>(&union_value);
    }
    typename std::add_pointer<const _traits_::TypeOf::natural8>::type get_natural8_if() const
    {
        return VariantType::get_if<VariantType::IndexOf::natural8>(&union_value);
    }
    typename std::add_lvalue_reference<_traits_::TypeOf::natural8>::type get_natural8()
    {
        
        return *VariantType::get_if<VariantType::IndexOf::natural8>(&union_value);
    }
    typename std::add_lvalue_reference<const _traits_::TypeOf::natural8>::type get_natural8() const
    {
        
        return *VariantType::get_if<VariantType::IndexOf::natural8>(&union_value);
    }
    template<class... Args> typename std::add_lvalue_reference<_traits_::TypeOf::natural8>::type
    set_natural8(Args&&...v)
    {
        return union_value.emplace<VariantType::IndexOf::natural8>(v...);
    }

    bool is_real64() const
    {
        return VariantType::IndexOf::real64 == union_value.index();
    }
    typename std::add_pointer<_traits_::TypeOf::real64>::type get_real64_if()
    {
        return VariantType::get_if<VariantType::IndexOf::real64>(&union_value);
    }
    typename std::add_pointer<const _traits_::TypeOf::real64>::type get_real64_if() const
    {
        return VariantType::get_if<VariantType::IndexOf::real64>(&union_value);
    }
    typename std::add_lvalue_reference<_traits_::TypeOf::real64>::type get_real64()
    {
        
        return *VariantType::get_if<VariantType::IndexOf::real64>(&union_value);
    }
    typename std::add_lvalue_reference<const _traits_::TypeOf::real64>::type get_real64() const
    {
        
        return *VariantType::get_if<VariantType::IndexOf::real64>(&union_value);
    }
    template<class... Args> typename std::add_lvalue_reference<_traits_::TypeOf::real64>::type
    set_real64(Args&&...v)
    {
        return union_value.emplace<VariantType::IndexOf::real64>(v...);
    }

    bool is_real32() const
    {
        return VariantType::IndexOf::real32 == union_value.index();
    }
    typename std::add_pointer<_traits_::TypeOf::real32>::type get_real32_if()
    {
        return VariantType::get_if<VariantType::IndexOf::real32>(&union_value);
    }
    typename std::add_pointer<const _traits_::TypeOf::real32>::type get_real32_if() const
    {
        return VariantType::get_if<VariantType::IndexOf::real32>(&union_value);
    }
    typename std::add_lvalue_reference<_traits_::TypeOf::real32>::type get_real32()
    {
        
        return *VariantType::get_if<VariantType::IndexOf::real32>(&union_value);
    }
    typename std::add_lvalue_reference<const _traits_::TypeOf::real32>::type get_real32() const
    {
        
        return *VariantType::get_if<VariantType::IndexOf::real32>(&union_value);
    }
    template<class... Args> typename std::add_lvalue_reference<_traits_::TypeOf::real32>::type
    set_real32(Args&&...v)
    {
        return union_value.emplace<VariantType::IndexOf::real32>(v...);
    }

    bool is_real16() const
    {
        return VariantType::IndexOf::real16 == union_value.index();
    }
    typename std::add_pointer<_traits_::TypeOf::real16>::type get_real16_if()
    {
        return VariantType::get_if<VariantType::IndexOf::real16>(&union_value);
    }
    typename std::add_pointer<const _traits_::TypeOf::real16>::type get_real16_if() const
    {
        return VariantType::get_if<VariantType::IndexOf::real16>(&union_value);
    }
    typename std::add_lvalue_reference<_traits_::TypeOf::real16>::type get_real16()
    {
        
        return *VariantType::get_if<VariantType::IndexOf::real16>(&union_value);
    }
    typename std::add_lvalue_reference<const _traits_::TypeOf::real16>::type get_real16() const
    {
        
        return *VariantType::get_if<VariantType::IndexOf::real16>(&union_value);
    }
    template<class... Args> typename std::add_lvalue_reference<_traits_::TypeOf::real16>::type
    set_real16(Args&&...v)
    {
        return union_value.emplace<VariantType::IndexOf::real16>(v...);
    }
};


inline nunavut::support::SerializeResult serialize(const Value_1_0& obj,
                                                   nunavut::support::bitspan out_buffer)
{
    const std::size_t capacity_bits = out_buffer.size();
    if ((static_cast<std::size_t>(capacity_bits)) < 2072UL)
    {
        return -nunavut::support::Error::SerializationBufferTooSmall;
    }
    // Notice that fields that are not an integer number of bytes long may overrun the space allocated for them
    // in the serialization buffer up to the next byte boundary. This is by design and is guaranteed to be safe.
    using VariantType = Value_1_0::VariantType;
    const auto _index0_ = obj.union_value.index();
    {   // Union tag field: truncated uint8
        const auto _result3_ = out_buffer.setUxx(_index0_, 8U);
        if(not _result3_){
            return -_result3_.error();
        }
        out_buffer.add_offset(8U);
    }
    if (VariantType::IndexOf::empty == _index0_)
    {
        auto _ptr0_ = obj.get_empty_if();
        std::size_t _size_bytes0_ = 0UL;  // Nested object (max) size, in bytes.
        auto _subspan0_ = out_buffer.subspan(0U, _size_bytes0_ * 8U);
        if(not _subspan0_){
            return -_subspan0_.error();
        }
        auto _err0_ = serialize((*_ptr0_), _subspan0_.value());
        if (not _err0_)
        {
            return _err0_;
        }
        _size_bytes0_ = _err0_.value();
        // It is assumed that we know the exact type of the serialized entity, hence we expect the size to match.
        out_buffer.add_offset(_size_bytes0_ * 8U);
        //
    }
    else if (VariantType::IndexOf::string == _index0_)
    {
        auto _ptr0_ = obj.get_string_if();
        std::size_t _size_bytes0_ = 258UL;  // Nested object (max) size, in bytes.
        auto _subspan0_ = out_buffer.subspan(0U, _size_bytes0_ * 8U);
        if(not _subspan0_){
            return -_subspan0_.error();
        }
        auto _err0_ = serialize((*_ptr0_), _subspan0_.value());
        if (not _err0_)
        {
            return _err0_;
        }
        _size_bytes0_ = _err0_.value();
        // It is assumed that we know the exact type of the serialized entity, hence we expect the size to match.
        out_buffer.add_offset(_size_bytes0_ * 8U);
        //
    }
    else if (VariantType::IndexOf::unstructured == _index0_)
    {
        auto _ptr0_ = obj.get_unstructured_if();
        std::size_t _size_bytes0_ = 258UL;  // Nested object (max) size, in bytes.
        auto _subspan0_ = out_buffer.subspan(0U, _size_bytes0_ * 8U);
        if(not _subspan0_){
            return -_subspan0_.error();
        }
        auto _err0_ = serialize((*_ptr0_), _subspan0_.value());
        if (not _err0_)
        {
            return _err0_;
        }
        _size_bytes0_ = _err0_.value();
        // It is assumed that we know the exact type of the serialized entity, hence we expect the size to match.
        out_buffer.add_offset(_size_bytes0_ * 8U);
        //
    }
    else if (VariantType::IndexOf::bit == _index0_)
    {
        auto _ptr0_ = obj.get_bit_if();
        std::size_t _size_bytes0_ = 258UL;  // Nested object (max) size, in bytes.
        auto _subspan0_ = out_buffer.subspan(0U, _size_bytes0_ * 8U);
        if(not _subspan0_){
            return -_subspan0_.error();
        }
        auto _err0_ = serialize((*_ptr0_), _subspan0_.value());
        if (not _err0_)
        {
            return _err0_;
        }
        _size_bytes0_ = _err0_.value();
        // It is assumed that we know the exact type of the serialized entity, hence we expect the size to match.
        out_buffer.add_offset(_size_bytes0_ * 8U);
        //
    }
    else if (VariantType::IndexOf::integer64 == _index0_)
    {
        auto _ptr0_ = obj.get_integer64_if();
        std::size_t _size_bytes0_ = 257UL;  // Nested object (max) size, in bytes.
        auto _subspan0_ = out_buffer.subspan(0U, _size_bytes0_ * 8U);
        if(not _subspan0_){
            return -_subspan0_.error();
        }
        auto _err0_ = serialize((*_ptr0_), _subspan0_.value());
        if (not _err0_)
        {
            return _err0_;
        }
        _size_bytes0_ = _err0_.value();
        // It is assumed that we know the exact type of the serialized entity, hence we expect the size to match.
        out_buffer.add_offset(_size_bytes0_ * 8U);
        //
    }
    else if (VariantType::IndexOf::integer32 == _index0_)
    {
        auto _ptr0_ = obj.get_integer32_if();
        std::size_t _size_bytes0_ = 257UL;  // Nested object (max) size, in bytes.
        auto _subspan0_ = out_buffer.subspan(0U, _size_bytes0_ * 8U);
        if(not _subspan0_){
            return -_subspan0_.error();
        }
        auto _err0_ = serialize((*_ptr0_), _subspan0_.value());
        if (not _err0_)
        {
            return _err0_;
        }
        _size_bytes0_ = _err0_.value();
        // It is assumed that we know the exact type of the serialized entity, hence we expect the size to match.
        out_buffer.add_offset(_size_bytes0_ * 8U);
        //
    }
    else if (VariantType::IndexOf::integer16 == _index0_)
    {
        auto _ptr0_ = obj.get_integer16_if();
        std::size_t _size_bytes0_ = 257UL;  // Nested object (max) size, in bytes.
        auto _subspan0_ = out_buffer.subspan(0U, _size_bytes0_ * 8U);
        if(not _subspan0_){
            return -_subspan0_.error();
        }
        auto _err0_ = serialize((*_ptr0_), _subspan0_.value());
        if (not _err0_)
        {
            return _err0_;
        }
        _size_bytes0_ = _err0_.value();
        // It is assumed that we know the exact type of the serialized entity, hence we expect the size to match.
        out_buffer.add_offset(_size_bytes0_ * 8U);
        //
    }
    else if (VariantType::IndexOf::integer8 == _index0_)
    {
        auto _ptr0_ = obj.get_integer8_if();
        std::size_t _size_bytes0_ = 258UL;  // Nested object (max) size, in bytes.
        auto _subspan0_ = out_buffer.subspan(0U, _size_bytes0_ * 8U);
        if(not _subspan0_){
            return -_subspan0_.error();
        }
        auto _err0_ = serialize((*_ptr0_), _subspan0_.value());
        if (not _err0_)
        {
            return _err0_;
        }
        _size_bytes0_ = _err0_.value();
        // It is assumed that we know the exact type of the serialized entity, hence we expect the size to match.
        out_buffer.add_offset(_size_bytes0_ * 8U);
        //
    }
    else if (VariantType::IndexOf::natural64 == _index0_)
    {
        auto _ptr0_ = obj.get_natural64_if();
        std::size_t _size_bytes0_ = 257UL;  // Nested object (max) size, in bytes.
        auto _subspan0_ = out_buffer.subspan(0U, _size_bytes0_ * 8U);
        if(not _subspan0_){
            return -_subspan0_.error();
        }
        auto _err0_ = serialize((*_ptr0_), _subspan0_.value());
        if (not _err0_)
        {
            return _err0_;
        }
        _size_bytes0_ = _err0_.value();
        // It is assumed that we know the exact type of the serialized entity, hence we expect the size to match.
        out_buffer.add_offset(_size_bytes0_ * 8U);
        //
    }
    else if (VariantType::IndexOf::natural32 == _index0_)
    {
        auto _ptr0_ = obj.get_natural32_if();
        std::size_t _size_bytes0_ = 257UL;  // Nested object (max) size, in bytes.
        auto _subspan0_ = out_buffer.subspan(0U, _size_bytes0_ * 8U);
        if(not _subspan0_){
            return -_subspan0_.error();
        }
        auto _err0_ = serialize((*_ptr0_), _subspan0_.value());
        if (not _err0_)
        {
            return _err0_;
        }
        _size_bytes0_ = _err0_.value();
        // It is assumed that we know the exact type of the serialized entity, hence we expect the size to match.
        out_buffer.add_offset(_size_bytes0_ * 8U);
        //
    }
    else if (VariantType::IndexOf::natural16 == _index0_)
    {
        auto _ptr0_ = obj.get_natural16_if();
        std::size_t _size_bytes0_ = 257UL;  // Nested object (max) size, in bytes.
        auto _subspan0_ = out_buffer.subspan(0U, _size_bytes0_ * 8U);
        if(not _subspan0_){
            return -_subspan0_.error();
        }
        auto _err0_ = serialize((*_ptr0_), _subspan0_.value());
        if (not _err0_)
        {
            return _err0_;
        }
        _size_bytes0_ = _err0_.value();
        // It is assumed that we know the exact type of the serialized entity, hence we expect the size to match.
        out_buffer.add_offset(_size_bytes0_ * 8U);
        //
    }
    else if (VariantType::IndexOf::natural8 == _index0_)
    {
        auto _ptr0_ = obj.get_natural8_if();
        std::size_t _size_bytes0_ = 258UL;  // Nested object (max) size, in bytes.
        auto _subspan0_ = out_buffer.subspan(0U, _size_bytes0_ * 8U);
        if(not _subspan0_){
            return -_subspan0_.error();
        }
        auto _err0_ = serialize((*_ptr0_), _subspan0_.value());
        if (not _err0_)
        {
            return _err0_;
        }
        _size_bytes0_ = _err0_.value();
        // It is assumed that we know the exact type of the serialized entity, hence we expect the size to match.
        out_buffer.add_offset(_size_bytes0_ * 8U);
        //
    }
    else if (VariantType::IndexOf::real64 == _index0_)
    {
        auto _ptr0_ = obj.get_real64_if();
        std::size_t _size_bytes0_ = 257UL;  // Nested object (max) size, in bytes.
        auto _subspan0_ = out_buffer.subspan(0U, _size_bytes0_ * 8U);
        if(not _subspan0_){
            return -_subspan0_.error();
        }
        auto _err0_ = serialize((*_ptr0_), _subspan0_.value());
        if (not _err0_)
        {
            return _err0_;
        }
        _size_bytes0_ = _err0_.value();
        // It is assumed that we know the exact type of the serialized entity, hence we expect the size to match.
        out_buffer.add_offset(_size_bytes0_ * 8U);
        //
    }
    else if (VariantType::IndexOf::real32 == _index0_)
    {
        auto _ptr0_ = obj.get_real32_if();
        std::size_t _size_bytes0_ = 257UL;  // Nested object (max) size, in bytes.
        auto _subspan0_ = out_buffer.subspan(0U, _size_bytes0_ * 8U);
        if(not _subspan0_){
            return -_subspan0_.error();
        }
        auto _err0_ = serialize((*_ptr0_), _subspan0_.value());
        if (not _err0_)
        {
            return _err0_;
        }
        _size_bytes0_ = _err0_.value();
        // It is assumed that we know the exact type of the serialized entity, hence we expect the size to match.
        out_buffer.add_offset(_size_bytes0_ * 8U);
        //
    }
    else if (VariantType::IndexOf::real16 == _index0_)
    {
        auto _ptr0_ = obj.get_real16_if();
        std::size_t _size_bytes0_ = 257UL;  // Nested object (max) size, in bytes.
        auto _subspan0_ = out_buffer.subspan(0U, _size_bytes0_ * 8U);
        if(not _subspan0_){
            return -_subspan0_.error();
        }
        auto _err0_ = serialize((*_ptr0_), _subspan0_.value());
        if (not _err0_)
        {
            return _err0_;
        }
        _size_bytes0_ = _err0_.value();
        // It is assumed that we know the exact type of the serialized entity, hence we expect the size to match.
        out_buffer.add_offset(_size_bytes0_ * 8U);
        //
    }
    else
    {
        return -nunavut::support::Error::RepresentationBadUnionTag;
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

inline nunavut::support::SerializeResult deserialize(Value_1_0& obj,
                                                     nunavut::support::const_bitspan in_buffer)
{
    const auto capacity_bits = in_buffer.size();
    using VariantType = Value_1_0::VariantType;
    // Union tag field: truncated uint8
    auto _index3_ = obj.union_value.index();
    _index3_ = in_buffer.getU8(8U);
    in_buffer.add_offset(8U);
    if (VariantType::IndexOf::empty == _index3_)
    {
        obj.set_empty();
        auto _ptr1_ = obj.get_empty_if();
        {
            std::size_t _size_bytes1_ = in_buffer.size() / 8U;
            {
                const auto _err1_ = deserialize((*_ptr1_), in_buffer.subspan());
                if(_err1_){
                    _size_bytes1_ = _err1_.value();
                }else{
                    return -_err1_.error();
                }
            }
            in_buffer.add_offset(_size_bytes1_ * 8U);  // Advance by the size of the nested serialized representation.
        }
    }
    else if (VariantType::IndexOf::string == _index3_)
    {
        obj.set_string();
        auto _ptr1_ = obj.get_string_if();
        {
            std::size_t _size_bytes1_ = in_buffer.size() / 8U;
            {
                const auto _err1_ = deserialize((*_ptr1_), in_buffer.subspan());
                if(_err1_){
                    _size_bytes1_ = _err1_.value();
                }else{
                    return -_err1_.error();
                }
            }
            in_buffer.add_offset(_size_bytes1_ * 8U);  // Advance by the size of the nested serialized representation.
        }
    }
    else if (VariantType::IndexOf::unstructured == _index3_)
    {
        obj.set_unstructured();
        auto _ptr1_ = obj.get_unstructured_if();
        {
            std::size_t _size_bytes1_ = in_buffer.size() / 8U;
            {
                const auto _err1_ = deserialize((*_ptr1_), in_buffer.subspan());
                if(_err1_){
                    _size_bytes1_ = _err1_.value();
                }else{
                    return -_err1_.error();
                }
            }
            in_buffer.add_offset(_size_bytes1_ * 8U);  // Advance by the size of the nested serialized representation.
        }
    }
    else if (VariantType::IndexOf::bit == _index3_)
    {
        obj.set_bit();
        auto _ptr1_ = obj.get_bit_if();
        {
            std::size_t _size_bytes1_ = in_buffer.size() / 8U;
            {
                const auto _err1_ = deserialize((*_ptr1_), in_buffer.subspan());
                if(_err1_){
                    _size_bytes1_ = _err1_.value();
                }else{
                    return -_err1_.error();
                }
            }
            in_buffer.add_offset(_size_bytes1_ * 8U);  // Advance by the size of the nested serialized representation.
        }
    }
    else if (VariantType::IndexOf::integer64 == _index3_)
    {
        obj.set_integer64();
        auto _ptr1_ = obj.get_integer64_if();
        {
            std::size_t _size_bytes1_ = in_buffer.size() / 8U;
            {
                const auto _err1_ = deserialize((*_ptr1_), in_buffer.subspan());
                if(_err1_){
                    _size_bytes1_ = _err1_.value();
                }else{
                    return -_err1_.error();
                }
            }
            in_buffer.add_offset(_size_bytes1_ * 8U);  // Advance by the size of the nested serialized representation.
        }
    }
    else if (VariantType::IndexOf::integer32 == _index3_)
    {
        obj.set_integer32();
        auto _ptr1_ = obj.get_integer32_if();
        {
            std::size_t _size_bytes1_ = in_buffer.size() / 8U;
            {
                const auto _err1_ = deserialize((*_ptr1_), in_buffer.subspan());
                if(_err1_){
                    _size_bytes1_ = _err1_.value();
                }else{
                    return -_err1_.error();
                }
            }
            in_buffer.add_offset(_size_bytes1_ * 8U);  // Advance by the size of the nested serialized representation.
        }
    }
    else if (VariantType::IndexOf::integer16 == _index3_)
    {
        obj.set_integer16();
        auto _ptr1_ = obj.get_integer16_if();
        {
            std::size_t _size_bytes1_ = in_buffer.size() / 8U;
            {
                const auto _err1_ = deserialize((*_ptr1_), in_buffer.subspan());
                if(_err1_){
                    _size_bytes1_ = _err1_.value();
                }else{
                    return -_err1_.error();
                }
            }
            in_buffer.add_offset(_size_bytes1_ * 8U);  // Advance by the size of the nested serialized representation.
        }
    }
    else if (VariantType::IndexOf::integer8 == _index3_)
    {
        obj.set_integer8();
        auto _ptr1_ = obj.get_integer8_if();
        {
            std::size_t _size_bytes1_ = in_buffer.size() / 8U;
            {
                const auto _err1_ = deserialize((*_ptr1_), in_buffer.subspan());
                if(_err1_){
                    _size_bytes1_ = _err1_.value();
                }else{
                    return -_err1_.error();
                }
            }
            in_buffer.add_offset(_size_bytes1_ * 8U);  // Advance by the size of the nested serialized representation.
        }
    }
    else if (VariantType::IndexOf::natural64 == _index3_)
    {
        obj.set_natural64();
        auto _ptr1_ = obj.get_natural64_if();
        {
            std::size_t _size_bytes1_ = in_buffer.size() / 8U;
            {
                const auto _err1_ = deserialize((*_ptr1_), in_buffer.subspan());
                if(_err1_){
                    _size_bytes1_ = _err1_.value();
                }else{
                    return -_err1_.error();
                }
            }
            in_buffer.add_offset(_size_bytes1_ * 8U);  // Advance by the size of the nested serialized representation.
        }
    }
    else if (VariantType::IndexOf::natural32 == _index3_)
    {
        obj.set_natural32();
        auto _ptr1_ = obj.get_natural32_if();
        {
            std::size_t _size_bytes1_ = in_buffer.size() / 8U;
            {
                const auto _err1_ = deserialize((*_ptr1_), in_buffer.subspan());
                if(_err1_){
                    _size_bytes1_ = _err1_.value();
                }else{
                    return -_err1_.error();
                }
            }
            in_buffer.add_offset(_size_bytes1_ * 8U);  // Advance by the size of the nested serialized representation.
        }
    }
    else if (VariantType::IndexOf::natural16 == _index3_)
    {
        obj.set_natural16();
        auto _ptr1_ = obj.get_natural16_if();
        {
            std::size_t _size_bytes1_ = in_buffer.size() / 8U;
            {
                const auto _err1_ = deserialize((*_ptr1_), in_buffer.subspan());
                if(_err1_){
                    _size_bytes1_ = _err1_.value();
                }else{
                    return -_err1_.error();
                }
            }
            in_buffer.add_offset(_size_bytes1_ * 8U);  // Advance by the size of the nested serialized representation.
        }
    }
    else if (VariantType::IndexOf::natural8 == _index3_)
    {
        obj.set_natural8();
        auto _ptr1_ = obj.get_natural8_if();
        {
            std::size_t _size_bytes1_ = in_buffer.size() / 8U;
            {
                const auto _err1_ = deserialize((*_ptr1_), in_buffer.subspan());
                if(_err1_){
                    _size_bytes1_ = _err1_.value();
                }else{
                    return -_err1_.error();
                }
            }
            in_buffer.add_offset(_size_bytes1_ * 8U);  // Advance by the size of the nested serialized representation.
        }
    }
    else if (VariantType::IndexOf::real64 == _index3_)
    {
        obj.set_real64();
        auto _ptr1_ = obj.get_real64_if();
        {
            std::size_t _size_bytes1_ = in_buffer.size() / 8U;
            {
                const auto _err1_ = deserialize((*_ptr1_), in_buffer.subspan());
                if(_err1_){
                    _size_bytes1_ = _err1_.value();
                }else{
                    return -_err1_.error();
                }
            }
            in_buffer.add_offset(_size_bytes1_ * 8U);  // Advance by the size of the nested serialized representation.
        }
    }
    else if (VariantType::IndexOf::real32 == _index3_)
    {
        obj.set_real32();
        auto _ptr1_ = obj.get_real32_if();
        {
            std::size_t _size_bytes1_ = in_buffer.size() / 8U;
            {
                const auto _err1_ = deserialize((*_ptr1_), in_buffer.subspan());
                if(_err1_){
                    _size_bytes1_ = _err1_.value();
                }else{
                    return -_err1_.error();
                }
            }
            in_buffer.add_offset(_size_bytes1_ * 8U);  // Advance by the size of the nested serialized representation.
        }
    }
    else if (VariantType::IndexOf::real16 == _index3_)
    {
        obj.set_real16();
        auto _ptr1_ = obj.get_real16_if();
        {
            std::size_t _size_bytes1_ = in_buffer.size() / 8U;
            {
                const auto _err1_ = deserialize((*_ptr1_), in_buffer.subspan());
                if(_err1_){
                    _size_bytes1_ = _err1_.value();
                }else{
                    return -_err1_.error();
                }
            }
            in_buffer.add_offset(_size_bytes1_ * 8U);  // Advance by the size of the nested serialized representation.
        }
    }
    else
    {
        return -nunavut::support::Error::RepresentationBadUnionTag;
    }
    in_buffer.align_offset_to<8U>();
    auto _bits_got_ = std::min<std::size_t>(in_buffer.offset(), capacity_bits);
    return { static_cast<std::size_t>(_bits_got_ / 8U) };
}

} // namespace _register
} // namespace uavcan

#endif // UAVCAN_REGISTER_VALUE_1_0_HPP_INCLUDED
