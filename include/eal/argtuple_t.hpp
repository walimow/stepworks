#pragma once

#include <tuple>

namespace stepworks::eal{

    template <typename...> struct argtuple_t;
    
    
    template <typename R, typename A>
    struct argtuple_t<R(A)>{
        R(_f)(A);
        using args_t = std::tuple<A>;
        
    };
    
    
    template <typename R, typename ...Args>
    struct argtuple_t<R(Args...)>{
        R(_f)(Args...);
        using args_t = std::tuple<Args...>;
      //  argtuple_t(R(*)(Args...)){}
    };
    
    
    
}
