#pragma once

#include <rw/winsert.hpp>

#include <list>
#include <forward_list>
using namespace std;

namespace stepworks::wtype
{


template <typename Ta, typename Position>
using dict_index = typename std::map<Ta, std::list<Position>   >   ;

template <typename Ta,   typename Position>
struct  insert<pair<Ta,Position>, dict_index > {
    dict_index<Ta,Position>&& _dest;
    constexpr  dict_index<Ta,Position> f1 ( const Ta&a ) const
    {
        auto & item = _dest [a.first];
        item.push_back ( a.second );
        return std::move ( _dest );
    }
    constexpr  bool f0() const
    {
        return std::move ( _dest );
    }

};


template<typename Ta, typename Pos,
         template<typename...>  typename Dest,
         template <typename > typename Form
         >
auto  _go_
(
    insert<  std::pair< Ta,Pos>,       Dest >&&        dest,
    Form<std::pair<Ta,Pos>>&& a_ )
->insert<
std::pair< Ta,Pos>,  Dest  >
{

    using kv = typename std::pair<Ta,Pos>;

    auto a0 = std::move ( a_ );
    return ( _x( insert< kv,dict_index > ( dest ) )) ( a0);  // apply_optional_void<  kv,dict_index >
}



}
