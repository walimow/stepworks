#pragma once


#include <core/optional_type.hpp>

#include <rw/wforward.hpp>
#include <rw/winsert.hpp>

#include <prim/wcontainer.hpp>

#include <type_traits>
#include <core/ftypetraits.hpp>

#include "apply_abstact.hpp"
#include "apply_type.hpp"
//#include  <utility>

using stepworks::types::var_t;

//using stepworks::wtype::_go_;


using stepworks::primary::_f_;

namespace stepworks::application
{


///apply writer:    a, w&&->w  (skip offs)
template <template<typename...>typename W, typename Ta >
struct apply <  W<Ta> ( W<Ta>&&, const Ta& ) > {
    W<Ta>&& _w;

    auto operator () ( const Ta& a )const
    {
        if constexpr ( has_member_f1t< decltype ( _w ), Ta >() ) {
            return _w.f1 (  a  );
        } else
            return    _f_ ( std::move ( _w ),  a );
    }

    ///TODO s. o.

    auto operator () ( const var_t<Ta>& a )const->W<Ta>
    {
        if ( a )
            return _go_ ( std::move ( _w ),  *a );
        else
            return std::move ( _w );
    }

    template <template<typename...>typename Form, typename Else >
    auto operator () ( const  Form<Ta, Else>& a )const
    {
        return _go_ ( std::move ( _w ),  a );
    }
///

    auto operator () ( Ta&& a )const
    {
        if constexpr ( has_member_f1t< decltype ( _w ), Ta >() ) {
            return _w.f1 ( std::move( a)  );

        } else
            return _f_ ( std::move ( _w ),  std::move ( a ) );
    }
    auto operator () ( var_t<Ta>&& a )const ->W<Ta>
    {
        if ( a )
            return _go_ ( _w , std::move ( *a ) );
        else
            return std::move ( _w );
    }

    template <template<typename...>typename Form, typename Else >
    auto operator () ( Form<Ta, Else>&& a )
    {
        return _go_ ( std::move ( _w ), std::move ( a ) );
    }
};



template <template<typename...>typename W, typename Ta>
auto _ ( W<Ta>&& w )
{
    return apply  <  W<Ta>  ( W<Ta>&&, const Ta& ) >  { std::move ( w )  };
}



///apply writer:    a, w&&->w  (skip offs)
template <typename K,typename Ta >
struct apply<std::map<K,Ta>&&,const Ta&> {
    std::map<K,Ta>&& _w;

    auto operator () ( const std::pair<K,Ta>& a )
    {
        return _f_ ( std::move ( _w ),  a );
    }
    auto operator () ( const var_t<std::pair<K, Ta>>& a )->std::map<K, Ta >
    {
        if ( a )
            return _go_ ( std::move ( _w ),  *a );
        else
            return std::move ( _w );
    }


    template <template<typename>typename Form >
    auto operator () ( const  Form<std::pair< K,Ta >>& a ) ->std::map<K,Ta>
    {
        return _go_ ( std::move ( _w ),  a );
    }
};



template <typename K,typename Ta, template<typename...>typename L >
struct apply<std::map<K,L<Ta>>&&,const Ta&> {
    std::map<K,L<Ta>>&& _w;
    auto operator () ( const std::pair<K,Ta>& a ) const ->std::map<K, L< Ta> >
    {
        auto & l = _w[a.first];
        _f_ ( l, a.second );
        return std::move ( _w );
    }

    template <template<typename>typename Form >
    auto operator () ( const  Form<std::pair< K,Ta >>& a ) const  ->std::map<K, L<Ta>>
    {
        return apply<
               std::pair< K,Ta >,
               apply<std::map<K,L<Ta>>&&,const Ta&>,
               std::map<K,L<Ta>>
               > {*this} ( a );
    }
    auto f0 () const
    {
        return std::move ( _w );
    }
    auto f1 ( const std::pair<K,Ta>& a ) const
    {
        return  _f_ ( std::move ( _w ),  a );
    }
};


template < typename K,typename Ta, template <typename...> typename L>
auto _ ( std::map<K, L<Ta>>&& w )
{
    return apply<std::map<K,   L<Ta>>&&, const Ta& > {std::move ( w ) };
}




template < typename K,typename Ta>
auto _ ( std::map<K,Ta>&& w )
{
    return apply<std::map<K, Ta>&&, const Ta& > {std::move ( w ) };
}


///////with predicate

///apply writer:    a, w&&->w  (skip offs)
template <template<typename...>typename W, typename Ta >
struct apply <  W<Ta> ( W<Ta>&&, const Ta& ),bool(const Ta&) > {
    W<Ta>&& _w;
    bool (*predicate)(const Ta&);
    
    auto operator () ( const Ta& a )const
    {
        if (!predicate(a))
            return std::move ( _w );
        
        if constexpr ( has_member_f1t< decltype ( _w ), Ta >() ) {
            return _w.f1 (  a  );
        } else
            return    _f_ ( std::move ( _w ),  a );
    }

    ///TODO s. o.

    auto operator () ( const var_t<Ta>& a )const->W<Ta>
    {
        
        if ( a   &&  predicate(a))
            return _go_ ( std::move ( _w ),  *a );
        else
            return std::move ( _w );
    }


    template <template<typename...>typename Form, typename Else >
    auto operator () ( const  Form<Ta, Else>& a )const
    {
        
        return  is_valid (a) ?   _go_ ( std::move ( _w ),  a ) 
        : std::move ( _w );
    }
///

    auto operator () ( Ta&& a )const
    {        
        if (!predicate(a))
            return std::move ( _w );        
        if constexpr ( has_member_f1t< decltype ( _w ), Ta >() ) {
            return _w.f1 ( std::move( a)  );

        } else
            return _f_ ( std::move ( _w ),  std::move ( a ) );
    }
    auto operator () ( var_t<Ta>&& a )const ->W<Ta>
    {
        if ( a &&  predicate(*a))
            return _go_ ( std::move ( _w ), std::move ( *a ) );
        else
            return std::move ( _w );
    }

    template <template<typename...>typename Form, typename Else >
    auto operator () ( Form<Ta, Else>&& a )
    {
        return _go_ ( std::move ( _w ), std::move ( a ) );
    }
};



template <template<typename...>typename W, typename Ta>
auto _ ( W<Ta>&& w , bool (*pred)(const Ta&))
{
    return apply  <  W<Ta> ( W<Ta>&&, const Ta& ),bool (const Ta&)  >  { std::move ( w ), pred  };
}





}
