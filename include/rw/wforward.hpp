#pragma once

#include <foab.first/isvalid.hpp>
//#include <xtypes.hpp>
#include <core/optional_type.hpp>
#include <core/optional.hpp>

#include <apply.hpp>

#include <iostream>  //test

using stepworks::types::var_t;
using stepworks::types::_asserted;
using stepworks::first::is_valid;
using stepworks::application::_;

namespace stepworks {

template <typename Ta,
          template<typename...>  typename Dest,
          template <typename > typename Form = var_t>
struct wforward {
    Dest<Ta>&& _dest; 
   
    constexpr  operator bool()const {        return true;    //?
    }

    struct wfoab {
        Dest<Ta>&&  _dest;
        using _argument_type=Ta;
        constexpr wforward operator ()(const Ta& a) const {
            std::move(_dest).push_back(a);
            return wforward {std::move(_dest)};
        }
        
        constexpr wforward operator ()(const Form<Ta>& a) const {
            if (_(is_valid<Ta>())(a)){
                ///test
                std::cout<< std::hex<<(int) _asserted<Ta>(a) <<". ";
                _dest.push_back( _asserted<Ta>(a));
            }
            return wforward {std::move(_dest)};
        }
        constexpr Dest<Ta> f0()const {
            return wforward {std::move(_dest)};
        }
    };

    struct wfoab_pred {
        Dest<Ta>&&  _dest;
        bool(*_pred)(const Ta&);
        using _argument_type=Ta;
        constexpr Dest<Ta> operator ()(const Ta& a) const {
            if (_pred(a))
                std::move(_dest).push_back(a);
            return wforward {std::move(_dest)};
        }

        constexpr Dest<Ta> operator ()(const var_t<Ta>& a) const {

            if (a  && _pred(*a)) {
                auto& dref= std::forward<decltype(Dest<Ta>())&> (_dest);
                std::cout<< std::hex<<(int) *a <<". ";
               
                 dref.push_back(*a);
            }
            return      std::move( _dest ) ;
        }
        constexpr Dest<Ta> f0()const {
            return wforward {std::move(_dest)};
        }
    };


};

template<typename Ta,
         template<typename ...>typename  Dest
         >
auto  _go_ ( wforward<Ta, Dest >&& dest, const var_t<Ta>& a0 ) {
    using W= wforward<Ta, Dest  >;

    auto w =  typename W::wfoab{ std::move(dest._dest)  }(a0);
    return std::move(w);
}


template<typename Ta,
         template<typename ...>typename  Dest
         >
auto  _go_  ( wforward<Ta, Dest >&& dest, const var_t<Ta>& a0, bool(*predicate)(const Ta&) )
{
  //  using WFw= wforward<Ta, Dest  >;
  //  using W= typename wforward<Ta, Dest  >::wfoab;

    wforward<Ta, Dest > s =std::move(dest);
    if (s && a0 )
    {
        using W= typename wforward<Ta, Dest  >::wfoab_pred;
        W { std::move(dest._dest), predicate}(a0);
    }
    return   s ;
}


template<typename Ta,
         template<typename ...>typename  Dest,
         template <typename > typename Form

         >
auto  _go_ ( wforward<Ta, Dest,Form >&& dest, const Form<Ta>& a0 )
{
    using W= typename wforward<Ta, Dest, Form  >::wfoab;

    wforward<Ta, Dest, Form > s =std::move(dest);
    if (s )
    {
          W   {std::move(dest._dest)}(a0) ;
    }
    return   std::move(s) ;
}


template<typename Ta,
         template<typename ...>typename  Dest,
         template <typename > typename Form=var_t

         >
auto  _go_ ( wforward<Ta, Dest,Form >&& dest, const Form<Ta>& a0,   bool (*predicate)(const Ta&))
{
    using W= typename wforward<Ta, Dest  >::wfoab_pred;

    wforward<Ta, Dest, Form > s =std::move(dest);
    if (s )
    {
        if ((a0) && predicate  )
        {

            return W{std::move(dest), predicate}(a0);
        };
    }
    return   std::move(s) ;
}


template<typename Ta,
         template<typename...>typename  Src,
         template <typename > typename Form
         >
auto  _go_ ( wforward<Ta, Src, Form  >&& src, Ta a )->wforward<Ta, Src, Form  >
{
  //  wforward<Ta, Src, Form > s =std::move(src);
  //  if (s  )
    ///////@@@@@@@
        std::move(src)._dest.push_back(a);   ///wg  forward_list
    return   std::move(src) ;
}



template<typename Ta,
         template<typename...>typename  Src,
         template <typename > typename Form
         >
auto  _go_ ( wforward<Ta, Src, Form  >&& src, const Ta& a, bool (*predicate)(const Ta&))
{
    wforward<Ta, Src, Form > s =std::move(src);
    if (s  && predicate(a) )
        s._dest.push_back(a);
    return   std::move(s) ;
}



}
