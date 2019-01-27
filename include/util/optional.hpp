#pragma once

#include "optional_type.hpp"
#include  <xtypes.hpp>
#include <foab.first/isvalid.hpp>

using stepworks::types::apply_optional_void;
using namespace stepworks::types;
using stepworks::first::is_valid;

namespace stepworks{
    namespace types{

template <typename Ta>
auto _optional(const var_t<Ta>& va, const Ta& _default){
    return (va) ? *va : _default;
}

///we have asked before...
template <typename Ta>
auto _asserted(const var_t<Ta>& va){
    return  *va ;
}

template <typename Ta, template< typename> typename Form>
auto _asserted(const Form<Ta>& va){
    return  (const Ta&) (va) ;
}


template <typename Ta>
auto _asserted(const Ta& a){
    return a ;
}

template <typename Ta>
auto _optional(const var_tx<Ta>& va, const Ta& _default){
    return ( apply_optional_void<int,bool>( va, is_valid<Ta>() )) ? *va : _default;
}

template <typename Ta>
auto _asserted(const var_tx<Ta>& va){
    return *va;
}


    }}

