#pragma once

#include <foab.first/isvalid.hpp>
#include <xtypes.hpp>
#include <util/optional_type.hpp>

using stepworks::types::var_t;

namespace stepworks {

template <typename Ta,
          template<typename...>  typename Dest,
          template <typename > typename Form = var_t>
struct wforward {
   Dest<Ta> _dest;

   constexpr  operator bool()const {
        return true;    //?
    }
    
    struct wfoab{
        Dest<Ta>&&  _dest;
        using _argument_type=Ta;
        constexpr Dest<Ta> operator ()(const Ta& a) const {
            std::move(_dest).push_back(a);
            return std::move(_dest);
        }
        constexpr Dest<Ta> operator ()(const Form<Ta>& a) const {
            //std::move(_dest).push_back(a);
            return std::move(_dest);
        }   
    };
};



/// Writer- Foab 
/*
template<typename Ta,
         template<typename...> typename  Dest ,
         template <typename > typename Form= var_t>
struct w_fw_o {
    Dest<Ta>&&  _dest;
    using _argument_type=Ta;
     constexpr Dest<Ta> operator ()(const Ta& a) const {
        std::move(_dest).push_back(a);
        return std::move(_dest);
    }
    constexpr Dest<Ta> operator ()(const Form<Ta>& a) const {
        //std::move(_dest).push_back(a);
        return std::move(_dest);
    }
};
*/


/*
template<typename Ta,
         template<typename ...>typename  Src,
         template <typename > typename Form= var_t
         >
auto  _go_ ( wforward<Ta, Src, Form  >&& src, const Form<Ta>& a0 )
{
    using W= typename wforward<Ta, Src, Form  >::wfoab;
    
    wforward<Ta, Src, Form > s =std::move(src);
    if (s )
    {
        return wforward<Ta, Src, Form  >
        {
            stepworks::apply_optional<  Ta , W  >( 
                a0, 
                W { std::move(s._dest)},
                []( const Ta& a,W&& w_)->W{ auto w=std::move(w_); w._dest.push_back(a); return std::move(w);}  )._dest
        };
    }
    return   std::move(s) ;
}

*/

template<typename Ta,
         template<typename ...>typename  Src
         >
auto  _go_ ( wforward<Ta, Src >&& src, const var_t<Ta>& a0 )
{
   
    using W= typename wforward<Ta, Src  >::wfoab;
    
    wforward<Ta, Src > s =std::move(src);
    if (s )
    {
        return wforward<Ta, Src  >
        {
            stepworks::apply_optional<  Ta , W  >( 
                a0, 
                W { std::move(s._dest)},
                []( const Ta& a,W&& w_)->W{ auto w=std::move(w_); w._dest.push_back(a); return std::move(w);}  )._dest
        };
    }
    return   std::move(s) ;
}


template<typename Ta,
         template<typename ...>typename  Src,
         template <typename > typename Form
 
         >
auto  _go_ ( wforward<Ta, Src,Form >&& src, const Form<Ta>& a0 )
{
    using W= typename wforward<Ta, Src, Form  >::wfoab;
    
    wforward<Ta, Src, Form > s =std::move(src);
    if (s )
    {
        return wforward<Ta, Src, Form  >
        {
            stepworks::apply_optional<  Ta , W ,Form >( 
                a0, 
                W { std::move(s._dest)},
                []( const Ta& a,W&& w_)->W{ auto w=std::move(w_); w._dest.push_back(a); return std::move(w);}  )._dest
        };
    }
    return   std::move(s) ;
}


template<typename Ta,
         template<typename...>typename  Src,
         template <typename > typename Form
         >
auto  _go_ ( wforward<Ta, Src, Form  >&& src, const Ta& a )
{
    wforward<Ta, Src, Form > s =std::move(src);
    if (s  )
        s._dest.push_back(a);
    return   std::move(s) ;
}



}
