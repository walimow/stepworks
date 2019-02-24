#pragma once


#include <util/optional_type.hpp>

#include <rw/wforward.hpp>
#include <rw/winsert.hpp>

#include <prim/wcontainer.hpp>

#include <type_traits>
//#include  <utility>

using stepworks::types::var_t;

//using stepworks::wtype::_go_;


using stepworks::primary::_f_;

namespace stepworks::application
{


///apply writer:    a, w&&->w  (skip offs)
template <typename Ta, template<typename...>typename W >
struct apply<W<Ta> ( W<Ta>&&, const Ta& ) > {
    W<Ta>&& _w;
    auto operator () ( const Ta& a )
    {
        return _f_ ( std::move ( _w ),  a );
    }
    auto operator () ( const var_t<Ta>& a )->W<Ta>
    {
        if ( a )
        return _go_ ( std::move ( _w ),  *a );
        else
            return std::move ( _w );
        }

        template <template<typename>typename Form >
auto operator () ( const  Form<Ta>& a )
    {
        return _go_ ( std::move ( _w ),  a );
    }
};



template <template<typename...>typename W, typename Ta>
auto _ ( W<Ta>&& w )
{
    return apply< W<Ta> ( W<Ta>&&, const Ta& ) > {std::move ( w ) };
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

    auto operator () ( const std::pair<K,Ta>& a )
    {
        return _f_ ( std::move ( _w ),  a );
    }
    auto operator () ( const var_t<std::pair<K, Ta>>& a )->std::map<K, L< Ta> >
    {
        if ( a ){
              auto & l =   std::move ( _w )[(*a).first];
              _f_ (l,(*a).second );
              return std::move ( _w );
        }
        //    return _f_ ( std::move ( _w ),  *a );
        else
            return std::move ( _w );
    }

    template <template<typename>typename Form >
    auto operator () ( const  Form<std::pair< K,Ta >>& a ) ->std::map<K, L<Ta>>
    {
        return _go_ ( std::move ( _w ),  a );
    }
};

/*
template <template<typename, typename>typename W, typename K,typename Ta>
auto _( W<K,Ta>&& w )
{
    return apply< W<K, Ta>(W<K, Ta>&&, const Ta&) > {std::move(w)};
}
*/


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




}
