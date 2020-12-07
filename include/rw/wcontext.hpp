//
// Created by karsten on 14.11.20.
//

#ifndef STEPWORKS_WCONTEXT_HPP
#define STEPWORKS_WCONTEXT_HPP

#include <utility>

namespace stepworks{

    //writing with context W(W&&, Ta&&, const Context) may be a value in an array on a position

  /*
template <typename Ta,
          template<typename...>  typename Dest,
          template <typename > typename Form = var_t>
struct wforward {
    Dest<Ta>&& _dest;

    constexpr  operator bool()const {        return true;    //?
    }*/

    template  < typename Ta,
            template< typename ...> typename Dest,
            typename  Context,
            typename  Tb=Ta >
    struct wcontext{
        //Dest<Ta> _dest;

        using apply_f= Tb(*)( Ta , Tb&& );

        static  Dest<Ta> _ (Dest<Ta>&& d, Ta&& a, const Context& x, apply_f app=[](Ta a, Tb&& b ){ return std::move(b+=a  ); } ){
            auto r =std::move(d)[ x ];
            r= app(std::move(r), std::move(a));
            return std::move(d);
        }

    };


}

#endif //STEPWORKS_WCONTEXT_HPP
