#pragma once
#include <tuple>
#include <eal/apply.hpp>
#include <util/tostrx.hpp>
#include <sstream>
#include <eal/curf.hpp>


namespace stepworks::eal {
    
    template <typename ...> struct lazy;


    template <typename F, typename ...Args>
    struct lazy<F, Args...>{
        using type_t = std::tuple<Args...>;
        type_t  _args;
        F&& _f;
        lazy(lazy&&)=default;
        lazy(type_t&& tt, F&& f  )
        :  _args( std::move(tt)),    _f (std::move(f))
        {};

        auto operator ()(){
            return stepworks::eal::apply( _f, _args);
        }
        auto args_to_string() const->std::string{
            return  tuple_to_string( _args );
        }
    };
    
    template <typename F, typename ...Args>
    auto _lazy_( F&& f, Args&&... args ){
        return   lazy<F,Args...>{std::make_tuple(args...), std::move(f) };
    }

}



namespace stepworks{

    template <typename F, typename ...Args>
    static auto to_string(const stepworks::eal::lazy<F, Args...> &v) {
        std::ostringstream ost;
        ost << "{f:{"
            << to_string(v._f)
            << "},args:{"
            << v.args_to_string()
            << "} }";
        return ost.str();
        //"--lazy--... structured output not yet implemented... ";         ////@TODO  meaningful output
    }
}
