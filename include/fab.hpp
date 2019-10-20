#pragma once

#include <foab.hpp>
#include <core/optional_type.hpp>
#include <core/offtype.hpp>


#include <util/argtype.hpp>
#include <util/arg_t.hpp>

//#include <xtypes.hpp>
#include <cassert>
#include <foab.hpp>


///Fab:    a->b,0-> b  , convinience for 0/a visitors f0: default/nothing handling without arg,  f1: existing argument a ->b  

namespace stepworks{
    
using argtool::arg_1_t;
    
template < typename  Foab, template <typename> typename Form  >
struct fab{
    const Foab& foab;
    //typename Ta, typename Tb,
    using Ta = arg_1_t<  typename  PM_traits< decltype (&Foab::operator()) >::member_type>;  //Error here: no fab
    using Tb = ret_t <  typename  PM_traits< decltype (&Foab::operator()) >::member_type>;
    
    using F0 = Form<Tb>(*)();
    F0 _f0;  
    auto f0()const {
        return _f0();
    }
    
    auto f1(const Ta& a)const {
        return foab( std::forward< Ta  >(  a   ));
    }
    
    
    static auto make(const Foab&foab, F0 f0= [](){ return Form<Tb>();})   {
        return fab{ foab, f0  };
    }
};
    
template < typename Foab_f,  template <typename> typename Form = stepworks::types::var_t  >
auto make_fab(const Foab_f& foab_f ){

    return fab< Foab_f, Form >::make(foab_f);
}


template < template <typename> typename Form , typename Foab_f    >
auto make_fab(const Foab_f& foab_f , typename  fab< Foab_f, Form >::F0 f0 ){

    return fab< Foab_f, Form >::make(foab_f, f0);
}




   
    
}


