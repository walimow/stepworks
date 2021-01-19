//
// Created by kh on 14.01.21.
//

#ifndef STEPWORKS_DETECT_FOAB_HPP
#define STEPWORKS_DETECT_FOAB_HPP

#include <type_traits>
#include <concepts>

namespace stepworks::detect{

    template< class, class, class,  class = void>
    struct is_foab : std::false_type {};

    template<typename F, typename Ta, typename Tb>
    struct is_foab<F, Ta,Tb,
            std::void_t<decltype(std::declval<F>().operator()( std::declval<Ta>()))>
    >
            ://std::true_type
                    std::is_same<
                            Tb,
                                    decltype( std::declval<F>()(std::declval<Ta>()))
                    >::type
    {};

    template<typename F, typename Ta, typename Tb>
    concept Foab = is_foab<F, Ta, Tb>::value;


}


#endif //STEPWORKS_DETECT_FOAB_HPP
