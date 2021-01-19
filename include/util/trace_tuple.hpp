#pragma once

#include <iostream>
#include <eal/ht.hpp>

namespace stepworks::util {

    using stepworks::eal::tail;
    using stepworks::eal::head;


template <typename Ty>
void trace_tuple( Ty&& a);

template <typename Ta, typename ...Args>
void trace_tuple( std::tuple<Ta,Args...>&& a);


template <typename Ty>
void trace_t_impl(Ty&& a) {
    std::cout << a << '\t';
}

void trace_t_impl(std::tuple<> a) { }

template <typename ...Ty, typename ...Rest>
void trace_t_impl( std::tuple< std::tuple<Ty...>, Rest...>&& a) {
    trace_t(head(std::move(a)));
    trace_t_impl(tail( std::move(a)));
}

template <typename Ty, typename ...Rest>
void trace_t_impl(std::tuple<Ty, Rest...>&& a) {
    std::cout << head(std::move(a)) << '\t';
    trace_t_impl(tail( std::move(a)));
}

template <typename Ty, typename ...Rest>
void trace_t_impl(const std::tuple<Ty, Rest...>& a) {
    std::cout << head(std::move(a)) << '\t';
    trace_t_impl(tail( std::move(a)));
}

/*
 * special clang, windows
template <typename Ty, typename Tz>
void trace_t_impl(std::tuple<Ty, Tz>&& a) {
	std::cout << head(std::move(a)) << '\t';
	std::cout<< head(tail(std::move(a)));
}
*/

template <typename Ty>
void trace_t_impl(std::tuple<Ty>&& a) {
    std::cout << head(std::move(a)) << '\t';
}

template <typename Ty>
void trace_tuple( Ty&& a)
{
    std::cout << a << '\t';
}

template <typename Ta>
void trace_tuple(std::tuple<Ta>&& a)
{
    std::cout << '<';
    trace_t_impl(a);
    std::cout << ">\t";
}

template <typename Ta, typename ...Args>
void trace_tuple( std::tuple<Ta,Args...>&& a)
{
    std::cout << '<';
    trace_t_impl<Ta,Args...>(std::move(a));
    std::cout << ">\t";
}

template <typename Ta, typename ...Args>
void trace_tuple(  const std::tuple<Ta,Args...>& a)
{
    std::cout << '<';
    trace_t_impl<Ta,Args...>(a);
    std::cout << ">\t";
}


template <typename Ta, typename ...Args>
void trace_tuple(   std::tuple<Ta,Args...>& a)
{
    std::cout << '<';
    trace_t_impl<Ta,Args...>(a);
    std::cout << ">\t";
}


}
