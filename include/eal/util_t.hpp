#pragma once

#include <tuple>
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




}
