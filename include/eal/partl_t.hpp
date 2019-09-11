#pragma once

#include "util_t.hpp"
#include "apply.hpp"


namespace stepworks::eal {

using stepworks::eal::head;
using stepworks::eal::tail;
    
using stepworks::eal::apply;

template <size_t N>
struct part_t {

	template <  typename... Ts >
	constexpr static auto left(  std::tuple<Ts...>&& t)
	{
     	return tail_implx<0>( std::make_index_sequence<N>(), t);
	}
	
	template <  typename... Ts >
	constexpr static auto right( std::tuple<Ts...>&& t)
	{
		return tail_implx<N>( std::make_index_sequence<sizeof...(Ts) - ( N)>(), t);
	}
	template <  typename... Ts >
	constexpr static auto lr(std::tuple<Ts...>&& t){
            return std::make_pair(left( std::move( t)), right( std::move( t)));
        }
        
        template <  typename F, typename... Ts >
	constexpr static auto lr_f(std::tuple<Ts...>&& t, F&& f){
            return std::make_pair( 
            stepworks::eal:: apply(  std::move(f), left(  std::move( t))), 
                                    right( std::move( t))
            );
        }
	
	template <  typename Fl, typename Fr, typename... Ts >
	constexpr static auto lr_ff(std::tuple<Ts...>&& t, Fl&& fl, Fr&& fr ){
            return std::make_pair( stepworks::eal::apply( std::move(fl), left(  std::move( t))),
                                   stepworks::eal::apply( std::move(fr), right( std::move( t)))
                                    );
        }

};
    
}
