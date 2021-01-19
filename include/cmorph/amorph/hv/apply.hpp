//
// Created by kh on 16.01.21.
//
#pragma once

#include <detect/detect_fa2box.hpp>

namespace stepworks::amorph::hv {

    using stepworks::bxx::box;

    using eSel = enum {
        eDefault, next, skip, up, down
    };

    //F (a)->box<Tb,C>
    template<typename Ta, typename F, template<typename...> typename C, typename Tb=Ta>
            requires(         stepworks::detect::is_function_a2box<F,Ta,Tb,C>::value)
    auto apply(const F &f, const Ta &a)-> typename box< Tb,C>::type {
        return f(a);
    }

// F()
/*
    template<typename Ta, typename Fcx, template<typename...> typename C, typename Tb=Ta> requires(
            stepworks::detect::is_function_aF2boxF<Fcx, Ta, Tb, C>::value)
    auto apply(  Fcx    && f,    const Ta &a    )->std::pair< box< Tb,C >,   Fcx> {
        return    f( f,  a);
    }
*/

//is_function_aF2boxF
template<typename Ta, template<typename...> typename C,  typename Fcx,typename Tb=Ta> requires(
        stepworks::detect::is_function_aF2boxF<Fcx, Ta, Tb, C>::value)
auto apply(  Fcx    && f,    const Ta &a    )->std::pair< typename box<Tb,C>::type , Fcx> {
return    f(  a,std::move(f));
}


//struct is_function_aCx2box<F,Ta,Tb,Cx, C,
template<typename Ta,  template<typename...> typename C, typename Cx, typename F,typename Tb=Ta> requires(
        stepworks::detect::is_function_aCx2box<F, Ta, Tb, Cx,C>::value)
auto apply(const F &f, const Ta &a, const Cx& cx)->typename box < Tb,C>::type {
    return f(a, cx) ;
}

//is_function_aCx2boxCx
template<typename Ta,  template<typename...> typename C, typename Cx, typename F,typename Tb=Ta> requires(
        stepworks::detect::is_function_aCx2boxCx<F, Ta, Tb, C,Cx>::value)
auto apply(const F &f, const Ta &a,  Cx&& cx)->    std::pair< typename box<Tb, C>::type , Cx>  {
return   f(a, std::move(cx)) ;
}

}

