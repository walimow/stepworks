#pragma once

#include "optional_type.hpp"
#include <foab.first/isvalid.hpp>

#include <cassert>

//using stepworks::types::apply_optional_void;
using namespace stepworks::types;
using stepworks::first::is_valid;

namespace stepworks{
    namespace types{

template <typename Ta>
auto _optional(const var_t<Ta>& va, const Ta& _default)->const Ta&{
    return (va) ? *va : _default;
}

///we have asked before...
template <typename Ta>
auto _asserted(const var_t<Ta>& va){
    return  *va ;
}

//maybe non-copyable cargo


template <typename Ta, template< typename...> typename Form, typename  Else>
auto _asserted(  Form<Else,Ta>&& va)->Ta{
    struct {
         auto operator()( Ta&&a)const { return std::move(a);}
         auto operator()( Else&&a)const { 
             assert(false);  return Ta(); 
        }   //<-ASSERTION FAILED!
        
    }vis;
    return std::visit(vis, std::move(va)) ;
}


template <typename Ta, template< typename...> typename Form, typename  Else>
auto _asserted( const Form<Else,Ta>& va)-> Ta{
    struct {
         auto operator()( const Ta&a) const { return a;}
         auto operator()( const Else&a) const  { assert(false); return Ta(); }   //<-ASSERTION FAILED!
        
    }vis;
    return std::visit(vis, va) ;
}


template <typename Ta>
auto _asserted(const Ta& a)->const Ta&{
    return a ;
}

template <typename Ta>
auto _optional(const var_tx<Ta>& va, const Ta& _default){    
    return  is_valid (va) ? std::get<1>(va)  : _default;
}



    }}

