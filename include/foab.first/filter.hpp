#pragma once
#include <util/optional_type.hpp>

using stepworks::types::var_t;

namespace stepworks::first{

    template <typename Ta>
    struct filter{
        using _arg=Ta;
       using Predicate= bool (*)(const Ta&); 
       const Predicate _pred;
       
      constexpr auto  operator  () ( Ta&& a) const->var_t<Ta> {
           return _pred(  std::forward<const Ta&> (a)) ?  std::move( a) : var_t<Ta>();
     }
       
       
       
    };
  
    /*
    template <typename Ta>
    filter<Ta >   make_filter( typename  filter<Ta>::Predicate f){
        return filter<Ta>{f};
    }*/
    
    
       
       
    
    
}
