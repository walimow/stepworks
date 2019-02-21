#pragma once
#include  <utility>

namespace stepworks{
    
    template <typename Ta>
    struct generator{
       using Frr = Ta(*)(Ta&&);
       Frr _f;
       Ta _state=0;
       
       constexpr auto operator()(){
           return std::make_pair(_state, generator<Ta> { _f, _f(std::move(_state))}) ;
    }
    };
    
    template <typename Ta>
    auto _go_(generator<Ta>&&g)->std::pair<Ta,generator<Ta>>{
        return std::move(g)();
    }
 //,  bool(*controlFunc)(const Ta,void*)
 
    template <typename Ta>
    generator<Ta> make_generator( typename generator<Ta>::Frr genFunc, Ta start_state=0 ){
        return generator<Ta>{genFunc,start_state };
    }
 
}
