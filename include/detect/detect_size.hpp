//
// Created by kh on 14.01.21.
//

#ifndef STEPWORKS_DETECT_SIZE_HPP
#define STEPWORKS_DETECT_SIZE_HPP

#include <type_traits>


namespace stepworks::detect {

    //has size
    template<typename C, typename=void>
    struct has_size : std::false_type {
    };

    template<typename C>
    struct has_size<C,
            std::void_t<
                    decltype(std::declval<C>().size())
            >
    > : std::is_same<
            std::size_t,
            decltype(std::declval<C>().size())
    >::type {
    };

}

#endif //STEPWORKS_DETECT_SIZE_HPP
