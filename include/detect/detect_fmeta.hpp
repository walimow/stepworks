//
// Created by kh on 29.10.21.
//

#pragma once

#include <type_traits>

namespace stepworks::detect{

    template<typename...> struct first_arg;
    template <typename R, typename T1, typename...Rest>
    struct  first_arg< R(*)(T1,Rest...)>{
        using ret_t=R;
        using type1=T1;
        using tpl_rest=std::tuple<Rest...>;
        using F=R(*)(T1,Rest...);
    };


    template<typename...> struct snd_arg;
    template <typename R, typename T1, typename T2, typename...Rest>
    struct  snd_arg< R(*)(T1,T2, Rest...)>{
        using ret_t=R;
        using type1=T1;
        using type2=T2;
        using tpl_rest=std::tuple<Rest...>;
        using F=R(*)(T1,T2, Rest...);
    };

    template<typename C, typename=void>
            struct second_arg_support : std::false_type {
            };

    template<typename C>
    struct second_arg_support<  C,   std::void_t
            <
            decltype( typename snd_arg< C  >::ret_t() )
            > > : std::true_type
            {  };


    template<typename C, typename=void>
            struct first_arg_support : std::false_type {
            };

    template<typename C>
    struct first_arg_support<  C,   std::void_t
            <
            decltype (typename first_arg< C> ::ret_t() )
            > > : std::true_type
            {  };

    template <typename Ty>
    concept SecondArgSupport = second_arg_support<Ty>::value;

    template <typename Ty>
    concept SingleArgSupport = first_arg_support<Ty>::value && ! second_arg_support<Ty>::value;


    template <typename Ty>
    concept FirstArgSupport = first_arg_support< Ty >::value ;

    struct no_param{};




}