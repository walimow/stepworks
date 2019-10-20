#pragma once
#include <tuple>
#include <eal/apply.hpp>


namespace stepworks::eal {
    
    template <typename ...> struct lazy_t;
 
    template <typename F, typename ...Args>
    struct lazy_t<F, Args...>{
        using type_t = std::tuple<Args...>;
        type_t  _args;
        F&& _f;
        
        auto operator ()(){
            return stepworks::eal::apply( _f, _args);
        }
    };
    
    template <typename F, typename ...Args>
    auto _lazy_( F&& f, Args&&... args ){
        return lazy_t<F,Args...>{ std::make_tuple(args...), std::move(f) };
    }

    ////todo....
    template <typename R, typename ...Args>
    struct lazy_t<R ( Args&&...)>{
        using type_t = std::tuple<Args...>;
        
        using Fnc = R(*)(Args...) ;
        type_t  _args;
        Fnc     _fnc;

    };
    
    
    
    
}
