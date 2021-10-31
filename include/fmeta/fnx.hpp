//
// Created by kh on 30.10.21.
//

#pragma once

//
// Created by karsten on 30.10.21.
//

#pragma once


#include <detect/detect_fmeta.hpp>
#include <type_traits>
#include <functional>

using stepworks::detect::SecondArgSupport;
using stepworks::detect::snd_arg;

using stepworks::detect::FirstArgSupport;
using stepworks::detect::first_arg;

using stepworks::detect::no_param;

namespace stepworks::fmeta{


    template <typename...>    struct fhh;

    template< typename R, typename  Ty>
    struct fhh<R,Ty>{

        const R& _fnc;
        Ty _a;
        template <typename Tb>
        auto operator()(Tb a){
            return  _fnc(_a, a);
        }
    };

    template< typename R, typename  Ty, typename... Args>
    struct fhh<R,Ty, Args...>{
     //   using Fx= R (*)(Ty, Args...);
        const R& _fnc;
        Ty _a;

        fhh(const R& r, const Ty& a):_fnc(r){
            _a=a;
        }

        template <typename Ta, typename ...As>
        auto operator()( Ta a,  As...as)const {

            return  fhh<R, Ta, Args...>{
                this
                , a }(as...);
        }
        auto operator()()const {
            return *this;
        }
    };



    template <typename ...>  struct fnx;

    template < typename R, typename Ta,typename...CContext>
    struct fnx<R,Ta, std::tuple<CContext...>>
     {
        using Fx= R (*)(Ta,  CContext... );
        Fx _fnc;

       // template<class M>
        auto operator ()(Ta a){
             return fhh<Fx,Ta>{_fnc,a};
        };

        auto operator ()(Ta a, CContext...cxs){
            return _fnc(a,cxs...);
        };

        ///partial call
        template<typename M, typename ...As>
        auto operator ()(Ta a, As...as){
            return fhh< M,Ta, As...> (_fnc,a )( as...);
        };
     };

    template<FirstArgSupport Fa, typename ...Rest>
    constexpr auto _fncx(Fa f){
       using R = typename first_arg<Fa,Rest...>::ret_t;
       using T1 = typename first_arg<Fa,Rest...>::type1;
       //using  T2= typename first_arg<Fa,Rest...>::type2;
       using tpl_rest= typename first_arg<Fa,Rest...>::tpl_rest;
       return fnx< R,T1, tpl_rest> { f };

    }
}