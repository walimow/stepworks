#pragma  once

#include "apply.hpp"
#include <tuple>

namespace stepworks::evaluation::ltype{
    
    template <typename...>struct le_t;
    
    template<typename F, typename...Args >
    
    struct le_t< F, Args...  >:  std::tuple<Args...>{
        le_t(F&& f, Args...args)
            :_f(std::move(f))  , std::tuple<Args...>{args...}
        {}
        F _f;
        constexpr const std::tuple<Args...>& args()const {
            return (const std::tuple<Args...>&)(*this);
        }
        constexpr auto operator()()const{
            return  stepworks::evaluation::apply(   _f, args() );
        }
    };
    
    template<typename F, typename...Args >
    auto make_le_t( F&& fo , Args... args ) {
        return le_t<F,Args... >(  std::move(fo) ,  std::move( args)... );
    }
    
    
    template<typename R, typename...Args >
    struct le_t<R(Args...)>:  std::tuple<Args...>{
        using F = R(*)(Args...);
        F _f;
        constexpr auto operator()(Args...args)const{
            return _f(args...);
        }
    };
    
    
    template<typename R, typename...Args >
    auto make_le_t( R(* f)(Args...)  , Args... args ) {
        return le_t<R(Args...),Args... >(  f ,  std::move( args)... );
    }

}

