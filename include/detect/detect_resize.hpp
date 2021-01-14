//
// Created by kh on 14.01.21.
//

#ifndef STEPWORKS_DETECT_RESIZE_HPP
#define STEPWORKS_DETECT_RESIZE_HPP

#include <type_traits>

namespace stepworks::detect{

    //has resize
    template<typename C, typename=void>
    struct supports_resize : std::false_type {
    };

    template<typename C>
    struct supports_resize<C,
            std::void_t<
                    decltype( std::declval<C>().resize( std::declval<std::size_t>() ) )
            >
    > : std::true_type {};

///construction with only size_t

    template<typename C, typename=void>
    struct supports_const_size : std::false_type {
    };

    template<typename C>
    struct supports_const_size<C,
            std::void_t<
                    std::is_nothrow_constructible< C, std::size_t>
            >
    > : std::true_type {};


}


#endif //STEPWORKS_DETECT_RESIZE_HPP
