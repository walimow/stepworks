#pragma once

#include <util/arg_n.hpp>


namespace stepworks{
    
    using arity_t = int;
    
    template <typename...>  struct _arity_;
    
    template <typename Ta>
    struct _arity_<Ta>{
        static const int value =0;
    }
    
    template <typename Ta, typename ...Args>
    struct _arity_<Ta(Args...)>{
        static const int value = argtool::arg_count<Args...>::value;
    }
    
    
    
    
    
    
}
