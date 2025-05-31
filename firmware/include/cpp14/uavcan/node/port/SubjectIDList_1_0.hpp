//
// This is an AUTO-GENERATED Cyphal DSDL data type implementation. Curious? See https://opencyphal.org.
// You shouldn't attempt to edit this file.
//
// Generator     : nunavut-3.0.0.dev1 (serialization was enabled)
// Source file   : SubjectIDList.1.0.dsdl
// Is deprecated : no
// Fixed port-ID : None
// Full name     : uavcan.node.port.SubjectIDList
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
#ifndef UAVCAN_NODE_PORT_SUBJECT_ID_LIST_1_0_HPP_INCLUDED
#define UAVCAN_NODE_PORT_SUBJECT_ID_LIST_1_0_HPP_INCLUDED

#include "nunavut/support/serialization.hpp"
#include "uavcan/node/port/SubjectID_1_0.hpp"
#include "uavcan/primitive/Empty_1_0.hpp"
#include <bitset>
#include <cstdint>
#include <limits>
#include <vector>

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
              "uavcan.node.port.SubjectIDList.1.0"
              "is trying to use a serialization library that was compiled with "
              "different language options. This is dangerous and therefore not "
              "allowed." );
static_assert( nunavut::support::options::omit_float_serialization_support == 0,
              "uavcan.node.port.SubjectIDList.1.0"
              "is trying to use a serialization library that was compiled with "
              "different language options. This is dangerous and therefore not "
              "allowed." );
static_assert( nunavut::support::options::omit_serialization_support == 0,
              "uavcan.node.port.SubjectIDList.1.0"
              "is trying to use a serialization library that was compiled with "
              "different language options. This is dangerous and therefore not "
              "allowed." );
static_assert( nunavut::support::options::enable_serialization_asserts == 0,
              "uavcan.node.port.SubjectIDList.1.0"
              "is trying to use a serialization library that was compiled with "
              "different language options. This is dangerous and therefore not "
              "allowed." );
static_assert( nunavut::support::options::enable_override_variable_array_capacity == 0,
              "uavcan.node.port.SubjectIDList.1.0"
              "is trying to use a serialization library that was compiled with "
              "different language options. This is dangerous and therefore not "
              "allowed." );
static_assert( nunavut::support::options::std == 3161622713,
              "uavcan.node.port.SubjectIDList.1.0"
              "is trying to use a serialization library that was compiled with "
              "different language options. This is dangerous and therefore not "
              "allowed." );
static_assert( nunavut::support::options::std_flavor == 2826573480,
              "uavcan.node.port.SubjectIDList.1.0"
              "is trying to use a serialization library that was compiled with "
              "different language options. This is dangerous and therefore not "
              "allowed." );
static_assert( nunavut::support::options::cast_format == 1407868567,
              "uavcan.node.port.SubjectIDList.1.0"
              "is trying to use a serialization library that was compiled with "
              "different language options. This is dangerous and therefore not "
              "allowed." );
static_assert( nunavut::support::options::variable_array_type_include == 3320664631,
              "uavcan.node.port.SubjectIDList.1.0"
              "is trying to use a serialization library that was compiled with "
              "different language options. This is dangerous and therefore not "
              "allowed." );
static_assert( nunavut::support::options::variable_array_type_template == 4227611599,
              "uavcan.node.port.SubjectIDList.1.0"
              "is trying to use a serialization library that was compiled with "
              "different language options. This is dangerous and therefore not "
              "allowed." );
static_assert( nunavut::support::options::variable_array_type_constructor_args == 0,
              "uavcan.node.port.SubjectIDList.1.0"
              "is trying to use a serialization library that was compiled with "
              "different language options. This is dangerous and therefore not "
              "allowed." );
static_assert( nunavut::support::options::allocator_include == 0,
              "uavcan.node.port.SubjectIDList.1.0"
              "is trying to use a serialization library that was compiled with "
              "different language options. This is dangerous and therefore not "
              "allowed." );
static_assert( nunavut::support::options::allocator_type == 0,
              "uavcan.node.port.SubjectIDList.1.0"
              "is trying to use a serialization library that was compiled with "
              "different language options. This is dangerous and therefore not "
              "allowed." );
static_assert( nunavut::support::options::allocator_is_default_constructible == 1,
              "uavcan.node.port.SubjectIDList.1.0"
              "is trying to use a serialization library that was compiled with "
              "different language options. This is dangerous and therefore not "
              "allowed." );
static_assert( nunavut::support::options::ctor_convention == 3814588639,
              "uavcan.node.port.SubjectIDList.1.0"
              "is trying to use a serialization library that was compiled with "
              "different language options. This is dangerous and therefore not "
              "allowed." );
static_assert( nunavut::support::options::variant_include == 0,
              "uavcan.node.port.SubjectIDList.1.0"
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
/// A list of subject identifiers.
/// The range of subject-ID is large, so using a fixed-size bitmask would make this type difficult to handle on
/// resource-constrained systems. To address that, we provide two extra options: a simple variable-length list,
/// and a special case that indicates that every subject-ID is in use.
///
struct SubjectIDList_1_0 final
{

    struct _traits_  // The name is surrounded with underscores to avoid collisions with DSDL attributes.
    {
        _traits_() = delete;
        /// This type does not have a fixed port-ID. See https://forum.opencyphal.org/t/choosing-message-and-service-ids/889
        static constexpr bool HasFixedPortID = false;

        static constexpr bool IsServiceType = false;

        static constexpr const char* FullNameAndVersion() { return "uavcan.node.port.SubjectIDList.1.0"; }
    
        /// Extent is the minimum amount of memory required to hold any serialized representation of any compatible
        /// version of the data type; or, on other words, it is the the maximum possible size of received objects of this type.
        /// The size is specified in bytes (rather than bits) because by definition, extent is an integer number of bytes long.
        /// When allocating a deserialization (RX) buffer for this data type, it should be at least extent bytes large.
        /// When allocating a serialization (TX) buffer, it is safe to use the size of the largest serialized representation
        /// instead of the extent because it provides a tighter bound of the object size; it is safe because the concrete type
        /// is always known during serialization (unlike deserialization). If not sure, use extent everywhere.
        static constexpr std::size_t ExtentBytes                  = 4097UL;
        static constexpr std::size_t SerializationBufferSizeBytes = 1025UL;
        static_assert(ExtentBytes >= SerializationBufferSizeBytes, "Internal constraint violation");
        static_assert(ExtentBytes < (std::numeric_limits<std::size_t>::max() / 8U), "This message is too large to be handled by the selected types");
        struct TypeOf
        {
            TypeOf() = delete;
            using mask = std::bitset<8192>;
            using sparse_list = std::vector<uavcan::node::port::SubjectID_1_0>;
            using total = uavcan::primitive::Empty_1_0;
        };
        struct ArrayCapacity
        {
            ArrayCapacity() = delete;
            static constexpr std::size_t mask = 8192UL;
            static constexpr std::size_t sparse_list = 255UL;
        };
    };

    
    // +---------------------------------------------------------------------------------------------------------------+
    // | CONSTANTS
    // +---------------------------------------------------------------------------------------------------------------+
    
    static constexpr std::uint16_t CAPACITY = 8192U;
    class VariantType final
    {
        std::size_t tag_;

        union internal_union_t
        {
            ///
            /// The index represents the identifier value. True -- present/used. False -- absent/unused.
            ///
            std::aligned_storage<sizeof(std::bitset<8192>), alignof(std::bitset<8192>)>::type mask;
            ///
            /// A list of identifiers that can be used instead of the mask if most of the identifiers are unused.
            ///
            std::aligned_storage<sizeof(std::vector<uavcan::node::port::SubjectID_1_0>), alignof(std::vector<uavcan::node::port::SubjectID_1_0>)>::type sparse_list;
            ///
            /// A special case indicating that all identifiers are in use.
            ///
            std::aligned_storage<sizeof(uavcan::primitive::Empty_1_0), alignof(uavcan::primitive::Empty_1_0)>::type total;
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
                    *reinterpret_cast<std::add_pointer<const std::bitset<8192>>::type>(&rhs.internal_union_value_.mask)
                );
            }
            else if(rhs.tag_ == 1)
            {
                do_copy<1>(
                    *reinterpret_cast<std::add_pointer<const std::vector<uavcan::node::port::SubjectID_1_0>>::type>(&rhs.internal_union_value_.sparse_list)
                );
            }
            else if(rhs.tag_ == 2)
            {
                do_copy<2>(
                    *reinterpret_cast<std::add_pointer<const uavcan::primitive::Empty_1_0>::type>(&rhs.internal_union_value_.total)
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
                    std::forward<std::bitset<8192>>(
                        *reinterpret_cast<std::add_pointer<std::bitset<8192>>::type>(&rhs.internal_union_value_.mask)
                    )
                );
            }
            else if(rhs.tag_ == 1)
            {
                do_emplace<1>(
                    std::forward<std::vector<uavcan::node::port::SubjectID_1_0>>(
                        *reinterpret_cast<std::add_pointer<std::vector<uavcan::node::port::SubjectID_1_0>>::type>(&rhs.internal_union_value_.sparse_list)
                    )
                );
            }
            else if(rhs.tag_ == 2)
            {
                do_emplace<2>(
                    std::forward<uavcan::primitive::Empty_1_0>(
                        *reinterpret_cast<std::add_pointer<uavcan::primitive::Empty_1_0>::type>(&rhs.internal_union_value_.total)
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
                    *reinterpret_cast<std::add_pointer<const std::bitset<8192>>::type>(&rhs.internal_union_value_.mask)
                );
            }
            else if(rhs.tag_ == 1)
            {
                do_copy<1>(
                    *reinterpret_cast<std::add_pointer<const std::vector<uavcan::node::port::SubjectID_1_0>>::type>(&rhs.internal_union_value_.sparse_list)
                );
            }
            else if(rhs.tag_ == 2)
            {
                do_copy<2>(
                    *reinterpret_cast<std::add_pointer<const uavcan::primitive::Empty_1_0>::type>(&rhs.internal_union_value_.total)
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
                    std::forward<std::bitset<8192>>(
                        *reinterpret_cast<std::add_pointer<std::bitset<8192>>::type>(&rhs.internal_union_value_.mask)
                    )
                );
            }
            else if(rhs.tag_ == 1)
            {
                do_emplace<1>(
                    std::forward<std::vector<uavcan::node::port::SubjectID_1_0>>(
                        *reinterpret_cast<std::add_pointer<std::vector<uavcan::node::port::SubjectID_1_0>>::type>(&rhs.internal_union_value_.sparse_list)
                    )
                );
            }
            else if(rhs.tag_ == 2)
            {
                do_emplace<2>(
                    std::forward<uavcan::primitive::Empty_1_0>(
                        *reinterpret_cast<std::add_pointer<uavcan::primitive::Empty_1_0>::type>(&rhs.internal_union_value_.total)
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
            static constexpr const std::size_t mask = 0U;
            static constexpr const std::size_t sparse_list = 1U;
            static constexpr const std::size_t total = 2U;
        };
        static constexpr const std::size_t MAX_INDEX = 3U;

        template<std::size_t I, class...Types> struct alternative;


        template<class...Types> struct alternative<0U, Types...>
        {
            using type = std::bitset<8192>;
            static constexpr auto pointer = &VariantType::internal_union_t::mask;
        };
        template<class...Types> struct alternative<1U, Types...>
        {
            using type = std::vector<uavcan::node::port::SubjectID_1_0>;
            static constexpr auto pointer = &VariantType::internal_union_t::sparse_list;
        };
        template<class...Types> struct alternative<2U, Types...>
        {
            using type = uavcan::primitive::Empty_1_0;
            static constexpr auto pointer = &VariantType::internal_union_t::total;
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
                reinterpret_cast<std::bitset<8192>*>(std::addressof(internal_union_value_.mask))->~bitset<8192>();
            }
            else if (tag_ == 1)
            {
                reinterpret_cast<std::vector<uavcan::node::port::SubjectID_1_0>*>(std::addressof(internal_union_value_.sparse_list))->~vector<uavcan::node::port::SubjectID_1_0>();
            }
            else if (tag_ == 2)
            {
                reinterpret_cast<uavcan::primitive::Empty_1_0*>(std::addressof(internal_union_value_.total))->~Empty_1_0();
            }
        }

    };

    VariantType union_value;


    bool is_mask() const
    {
        return VariantType::IndexOf::mask == union_value.index();
    }
    typename std::add_pointer<_traits_::TypeOf::mask>::type get_mask_if()
    {
        return VariantType::get_if<VariantType::IndexOf::mask>(&union_value);
    }
    typename std::add_pointer<const _traits_::TypeOf::mask>::type get_mask_if() const
    {
        return VariantType::get_if<VariantType::IndexOf::mask>(&union_value);
    }
    typename std::add_lvalue_reference<_traits_::TypeOf::mask>::type get_mask()
    {
        
        return *VariantType::get_if<VariantType::IndexOf::mask>(&union_value);
    }
    typename std::add_lvalue_reference<const _traits_::TypeOf::mask>::type get_mask() const
    {
        
        return *VariantType::get_if<VariantType::IndexOf::mask>(&union_value);
    }
    template<class... Args> typename std::add_lvalue_reference<_traits_::TypeOf::mask>::type
    set_mask(Args&&...v)
    {
        return union_value.emplace<VariantType::IndexOf::mask>(v...);
    }

    bool is_sparse_list() const
    {
        return VariantType::IndexOf::sparse_list == union_value.index();
    }
    typename std::add_pointer<_traits_::TypeOf::sparse_list>::type get_sparse_list_if()
    {
        return VariantType::get_if<VariantType::IndexOf::sparse_list>(&union_value);
    }
    typename std::add_pointer<const _traits_::TypeOf::sparse_list>::type get_sparse_list_if() const
    {
        return VariantType::get_if<VariantType::IndexOf::sparse_list>(&union_value);
    }
    typename std::add_lvalue_reference<_traits_::TypeOf::sparse_list>::type get_sparse_list()
    {
        
        return *VariantType::get_if<VariantType::IndexOf::sparse_list>(&union_value);
    }
    typename std::add_lvalue_reference<const _traits_::TypeOf::sparse_list>::type get_sparse_list() const
    {
        
        return *VariantType::get_if<VariantType::IndexOf::sparse_list>(&union_value);
    }
    template<class... Args> typename std::add_lvalue_reference<_traits_::TypeOf::sparse_list>::type
    set_sparse_list(Args&&...v)
    {
        return union_value.emplace<VariantType::IndexOf::sparse_list>(v...);
    }

    bool is_total() const
    {
        return VariantType::IndexOf::total == union_value.index();
    }
    typename std::add_pointer<_traits_::TypeOf::total>::type get_total_if()
    {
        return VariantType::get_if<VariantType::IndexOf::total>(&union_value);
    }
    typename std::add_pointer<const _traits_::TypeOf::total>::type get_total_if() const
    {
        return VariantType::get_if<VariantType::IndexOf::total>(&union_value);
    }
    typename std::add_lvalue_reference<_traits_::TypeOf::total>::type get_total()
    {
        
        return *VariantType::get_if<VariantType::IndexOf::total>(&union_value);
    }
    typename std::add_lvalue_reference<const _traits_::TypeOf::total>::type get_total() const
    {
        
        return *VariantType::get_if<VariantType::IndexOf::total>(&union_value);
    }
    template<class... Args> typename std::add_lvalue_reference<_traits_::TypeOf::total>::type
    set_total(Args&&...v)
    {
        return union_value.emplace<VariantType::IndexOf::total>(v...);
    }
};


inline nunavut::support::SerializeResult serialize(const SubjectIDList_1_0& obj,
                                                   nunavut::support::bitspan out_buffer)
{
    const std::size_t capacity_bits = out_buffer.size();
    if ((static_cast<std::size_t>(capacity_bits)) < 8200UL)
    {
        return -nunavut::support::Error::SerializationBufferTooSmall;
    }
    // Notice that fields that are not an integer number of bytes long may overrun the space allocated for them
    // in the serialization buffer up to the next byte boundary. This is by design and is guaranteed to be safe.
    using VariantType = SubjectIDList_1_0::VariantType;
    const auto _index0_ = obj.union_value.index();
    {   // Union tag field: truncated uint8
        const auto _result3_ = out_buffer.setUxx(_index0_, 8U);
        if(not _result3_){
            return -_result3_.error();
        }
        out_buffer.add_offset(8U);
    }
    if (VariantType::IndexOf::mask == _index0_)
    {
        auto _ptr0_ = obj.get_mask_if();
        const std::size_t _origin0_ = out_buffer.offset();
        for (std::size_t _index1_ = 0U; _index1_ < 8192UL; ++_index1_)
        {
            auto _result2_ = out_buffer.setBit((*_ptr0_)[_index1_]);
            if(not _result2_){
                return -_result2_.error();
            }
            out_buffer.add_offset(1UL);
        }
        // It is assumed that we know the exact type of the serialized entity, hence we expect the size to match.
        (void) _origin0_;
    }
    else if (VariantType::IndexOf::sparse_list == _index0_)
    {
        auto _ptr0_ = obj.get_sparse_list_if();
        if ((*_ptr0_).size() > 255)
        {
            return -nunavut::support::Error::SerializationBadArrayLength;
        }
        // Array length prefix: truncated uint8
        const auto _result3_ = out_buffer.setUxx((*_ptr0_).size(), 8U);
        if(not _result3_){
            return -_result3_.error();
        }
        out_buffer.add_offset(8U);
        for (std::size_t _index2_ = 0U; _index2_ < (*_ptr0_).size(); ++_index2_)
        {
            std::size_t _size_bytes0_ = 2UL;  // Nested object (max) size, in bytes.
            auto _subspan0_ = out_buffer.subspan(0U, _size_bytes0_ * 8U);
            if(not _subspan0_){
                return -_subspan0_.error();
            }
            auto _err0_ = serialize((*_ptr0_)[_index2_], _subspan0_.value());
            if (not _err0_)
            {
                return _err0_;
            }
            _size_bytes0_ = _err0_.value();
            // It is assumed that we know the exact type of the serialized entity, hence we expect the size to match.
            out_buffer.add_offset(_size_bytes0_ * 8U);
            //
        }
    }
    else if (VariantType::IndexOf::total == _index0_)
    {
        auto _ptr0_ = obj.get_total_if();
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

inline nunavut::support::SerializeResult deserialize(SubjectIDList_1_0& obj,
                                                     nunavut::support::const_bitspan in_buffer)
{
    const auto capacity_bits = in_buffer.size();
    using VariantType = SubjectIDList_1_0::VariantType;
    // Union tag field: truncated uint8
    auto _index3_ = obj.union_value.index();
    _index3_ = in_buffer.getU8(8U);
    in_buffer.add_offset(8U);
    if (VariantType::IndexOf::mask == _index3_)
    {
        obj.set_mask();
        auto _ptr1_ = obj.get_mask_if();
        for (std::size_t _index4_ = 0U; _index4_ < 8192UL; ++_index4_)
        {
            (*_ptr1_)[_index4_] = in_buffer.getBit();
            in_buffer.add_offset(1U);
        }
    }
    else if (VariantType::IndexOf::sparse_list == _index3_)
    {
        obj.set_sparse_list();
        auto _ptr1_ = obj.get_sparse_list_if();
        {
            // Array length prefix: truncated uint8
        const std::size_t _size0_ = in_buffer.getU8(8U);
        in_buffer.add_offset(8U);
            if ( _size0_ > 255U)
            {
                return -nunavut::support::Error::SerializationBadArrayLength;
            }
            (*_ptr1_).reserve(_size0_);
            for (std::size_t _index5_ = 0U; _index5_ < _size0_; ++_index5_)
            {
                uavcan::node::port::SubjectID_1_0 _tmp0_ = uavcan::node::port::SubjectID_1_0();
                {
                std::size_t _size_bytes1_ = in_buffer.size() / 8U;
                {
                    const auto _err1_ = deserialize(_tmp0_, in_buffer.subspan());
                    if(_err1_){
                        _size_bytes1_ = _err1_.value();
                    }else{
                        return -_err1_.error();
                    }
                }
                in_buffer.add_offset(_size_bytes1_ * 8U);  // Advance by the size of the nested serialized representation.
            }
                (*_ptr1_).push_back(std::move(_tmp0_));
            }
        }
    }
    else if (VariantType::IndexOf::total == _index3_)
    {
        obj.set_total();
        auto _ptr1_ = obj.get_total_if();
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

} // namespace port
} // namespace node
} // namespace uavcan

#endif // UAVCAN_NODE_PORT_SUBJECT_ID_LIST_1_0_HPP_INCLUDED
