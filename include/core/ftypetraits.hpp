#pragma once 

#include <type_traits>

namespace stepworks{
    
    
    
template <typename T, typename = void>
struct has_member_f0
    : std::false_type
{};

template <typename T>
struct has_member_f0<T,
       std::void_t<decltype(std::declval<T>().f0())>>
       : std::true_type
       {};

/*
template <typename T, typename = void>
struct has_member_f1
    : std::false_type
{};

template <typename T>
struct has_member_f1<T,
       std::void_t<decltype(std::declval<T>().f1(1))>>
       : std::true_type
       {};

*/       
       
template <typename T, typename Arg, typename = void>
struct has_member_f1t
    : std::false_type
{};


template <typename T, typename Arg>
struct has_member_f1t<T,Arg,
       std::void_t<decltype(std::declval<T>().f1(std::declval<Arg>()))>>
       : std::true_type
       {};




template <typename T, typename = void>
struct has_member_ft
    : std::false_type
{};


template <typename T>
struct has_member_ft<T,
       std::void_t<decltype(std::declval<T>().Ft(1))>>
       : std::true_type
       {};



    
}
