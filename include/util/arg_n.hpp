#pragma once

namespace argtool{
    ///////argcount

template <typename...> struct arg_count;

//0
template <typename R>
struct arg_count<R()>
{
       static int const value= 0;
};

//1
template <typename R, typename A>
struct arg_count<R(A)>
{
    static int const value= 1;
};

template <typename R, typename A>
struct arg_count<R(A)const>
{
    static int const value= 1;
};


template <typename R, typename Cls, typename A>
struct arg_count<R (Cls::*)(A)const>
{
    static int const value= 1;
};

template <typename R, typename Cls, typename A>
struct arg_count<R (Cls::*)(A)>
{
    static int const value= 1;
};

//n 

template <typename R, typename A, typename...Args>
struct arg_count<R(A, Args...)>
{
    static int const value= 1+ arg_count<R, Args...>::value;
};

template <typename R, typename A, typename...Args>
struct arg_count<R(A, Args...)const >
{
    static int const value= 1+ arg_count<R, Args...>::value;
};


template <typename R,  typename Cls, typename A, typename...Args>
struct arg_count<R(Cls::*)(A, Args...)const >
{
    static int const value= 1+ arg_count<R(Cls::*)( Args...)const>::value;
};


template <typename R,  typename Cls, typename A, typename...Args>
struct arg_count<R(Cls::*)(A, Args...) >
{
    static int const value= 1+ arg_count<R(Cls::*)(Args...)>::value;
};


    
    
}
