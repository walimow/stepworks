//
// Created by kh on 21.12.20.
//

#ifndef STEPWORKS_DETECT_FO_HPP
#define STEPWORKS_DETECT_FO_HPP

#include <type_traits>
#include <>
namespace stepworks::detect {

    /*
     template <typename T, typename Arg>
struct has_operator_t<T,Arg,
       std::void_t<decltype(std::declval<T>().operator()( std::declval<Arg>()))>>
       : std::true_type
       {};

     * */

    template< class, class = void>
    struct is_function_type : std::false_type {};

    template<typename F, typename ...Args>
    struct is_function_type<F,
            std::void_t<decltype(std::declval<T>().operator()( std::declval<Arg...>()))>
            >
            :std::true_type
    {};

    template< class, class = void>
    struct has_bounded_args : std::false_type {};

    template<typename F, typename ...Args>
    struct has_bounded_args<F,
            std::void_t<decltype(std::declval<T>()._args)>
    >
            :std::true_type
    {};


}

#endif //STEPWORKS_DETECT_FO_HPP
