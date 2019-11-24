#pragma once

#include <tuple>
#include <array>
#include "ht.hpp"
#include "apply.hpp"

namespace stepworks::eal {

template <typename T>
constexpr size_t tuple_sz(T&& ign) {
    return 0;
}


template <typename ...Args>
constexpr size_t tuple_sz(std::tuple<Args...> ) {
    return std::tuple_size< std::tuple<Args...>   >::value;
}


template <typename ...> struct _sz_;

template <typename Ta> 
struct _sz_<Ta>{
    static const size_t value=1;
};

template <typename ...Args> 
struct _sz_<std::tuple<Args...>>{
    static const size_t value= _sz_<Args...>::value ;
};

template <> 
struct _sz_<>{
    static const size_t value=0;
};

template <typename Ta , std::size_t SZ> 
struct _sz_< std::array<Ta,SZ> >{
    static const size_t value=SZ;
};

template <typename Ta, typename ...Args> 
struct _sz_<Ta,Args...>{
    static const size_t value=1 + _sz_<Args...>::value;
};

template <typename L, typename R>
constexpr bool sz_eq( L&&l, R&&r )noexcept {
    return tuple_sz(l)==tuple_sz(r);
}

template <typename L, typename R>
constexpr bool sz_ls( L&&l, R&&r )noexcept {
    return tuple_sz(l)<tuple_sz(r);
}

template <typename L, typename R>
constexpr bool sz_gt( L&&l, R&&r )noexcept {
    return tuple_sz(l)>tuple_sz(r);
}

template<typename Ty, typename Ta,  typename...Args>
constexpr bool yappliable( const Ty& y,  std::tuple<Ta,Args...>&&args) {
    return std::is_assignable<Ta&,Ty>
           ::value;
}


template <typename ...> struct htype;

template <typename Ta>
struct htype<Ta>{
    using type =Ta;
};

template <typename Ta, typename...Rest>
struct htype<std::tuple<Ta, Rest...>>{
    using type =Ta;
};


template <typename Ta, typename...Rest>
struct htype<Ta, Rest...>{
    using type =Ta;
};


//template <typename Ty>




}
