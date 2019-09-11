#pragma once

#include <tuple>


namespace stepworks::eal {
 
template < typename T, typename... Ts >
auto head(std::tuple<T, Ts...> t)
{
     return  std::get<0>(t);
}

 

template < std::size_t... Ns, typename... Ts >
auto tail_impl(std::index_sequence<Ns...>, std::tuple<Ts...> t)
{
     return  std::make_tuple(std::get<Ns + 1u>(t)...);
}

///r.rest of a left partition
template < std::size_t D, std::size_t... Ns, typename... Ts >
auto tail_implx(std::index_sequence<Ns...>, std::tuple<Ts...> t)
{
	return  std::make_tuple(std::get<Ns + D>(t)...);
}
 

template < typename... Ts >
auto tail(std::tuple<Ts...> t)
{
     return  tail_impl(std::make_index_sequence<sizeof...(Ts) - 1u>(), t);
}

///head_tail

template < std::size_t... Ns, typename... Ts >
auto head_tail_impl(std::index_sequence<Ns...>, std::tuple<Ts...> t)
{
     return  std::make_pair( head(t), std::make_tuple(std::get<Ns + 1u>(t)...));
}
 
template < typename... Ts >
auto head_tail(std::tuple<Ts...> t)
{
     return  head_tail_impl(std::make_index_sequence<sizeof...(Ts) - 1u>(), t);
} 

///fhead_tail

template < typename F, std::size_t... Ns, typename... Ts >
auto fhead_tail_impl(F&& f, std::index_sequence<Ns...>, std::tuple<Ts...> t)
{
     return  std::make_pair(f( head(t)), std::make_tuple(std::get<Ns + 1u>(t)...));
}
 
template < typename F,typename ... Ts >
auto fhead_tail(F&&f, std::tuple<Ts...> t)
{
     return  head_tail_impl(std::move(f), std::make_index_sequence<sizeof...(Ts) - 1u>(), t);
} 

///ffhead_tail

template < typename Fh, typename Ft, std::size_t... Ns, typename... Ts >
auto ffhead_tail_impl(Fh&& fh, Ft&& ft,  std::index_sequence<Ns...>, std::tuple<Ts...> t)
{
     return  std::make_pair(fh( head(t)), ft( std::make_tuple(std::get<Ns + 1u>(t)...)));
}
 
template < typename Fh, typename Ft,typename ... Ts >
auto ffhead_tail(Fh&&fh, Ft&& ft, std::tuple<Ts...> t)
{
     return  head_tail_impl(std::move(fh), std::move(ft), std::make_index_sequence<sizeof...(Ts) - 1u>(), t);
} 



}
