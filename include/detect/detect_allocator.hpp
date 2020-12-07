//
// Created by kh on 23.11.20.
//

#ifndef STEPWORKS_DETECT_ALLOCATOR_TYPE_HPP
#define STEPWORKS_DETECT_ALLOCATOR_TYPE_HPP

#include <type_traits>
#include <concepts>

namespace stepworks::detect {

    template<typename Ty, typename=void>
    struct has_allocator: std::false_type {
    };

    ///has type allocator_type
    template<typename Ty>
    struct has_allocator<Ty, std::void_t<
            decltype(std::declval<typename Ty::allocator_type>())
    > > : std::true_type {
    };



    template< typename C>
    concept Allocated= has_allocator<C>::value;

}

#endif //STEPWORKS_DETECT_ALLOCATOR_TYPE_HPP
