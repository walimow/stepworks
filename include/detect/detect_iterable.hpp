//
// Created by kh on 01.12.20.
//

#ifndef BOX_DETECT_ITERABLE_HPP
#define BOX_DETECT_ITERABLE_HPP

#include <type_traits>


namespace stepworks::detect {

    template<typename C, typename=void>
    struct is_forward_iterable : std::false_type {
    };

    template<typename C>
    struct is_forward_iterable<C,
                    std::void_t<
                        decltype(std::declval<C>().begin()
                                 ,            std::declval<C>().end()
                                 ,            std::declval<C>().begin()++
                                               )
                        >
                    > : std::true_type {
    };

}



#endif //BOX_DETECT_ITERABLE_HPP
