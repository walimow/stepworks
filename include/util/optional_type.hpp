#pragma once

#include <variant>
#include <optional>
#include <util/offtype.hpp>

#include <none.hpp>

namespace stepworks{
    namespace types{

        
template <typename Ta>
using var_t = std::optional<Ta>;

//using var_t =std::optional;        
        

template <typename Ta>
struct off_type{
    Ta _data;
};


template <typename Ta>
struct off_type_num{
    Ta _data;
    int _num;
};


template <typename Ta, typename Tx=Ta>    //may contain an instance of another or the same type
using var_t_type =std::variant< off_type<Tx> ,Ta>;


template <typename Ta, typename Tx=off_info>
using var_tx = std::variant<  Tx ,Ta>;

template <typename Ta>
using  var_t_info = var_tx<Ta,off_info>;


template<typename ...> struct var_type;

template<typename Ta>
struct var_type<var_t<Ta>>{
    using _Type = Ta;
 //   using _Form = 1;
    using  _Off  = _none_;
};


template<typename Ta, typename Off>
struct var_type< var_t_type<Ta,Off> >{
    using _Type = Ta;
//    using _Form = 2;
    using  _Off  = Off;
};


template<typename Ta, typename Off>
struct var_type< var_tx<Ta,Off> >{
    using _Type = Ta;
//    using _Form = 3;
    using  _Off  = Off;
};


/*
 
template <typename Ta>
auto _optional(const _TI<Ta>& a, const Ta& _default_)->Ta {
    struct visitor{
        const Ta& _default_;
        auto operator()(const _none_ &)const{ return  _default_; }
        auto operator()(const undefined &)const{ return  _default_; }
       
       auto operator()(const Ta & a)const{ return a; }
    };
    return std::visit(visitor{ _default_ },a);
}
 */

        
    }}
