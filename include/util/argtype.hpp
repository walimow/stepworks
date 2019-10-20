#pragma once


template<typename>
struct PM_traits {};

template<class T, class U>
struct PM_traits<U T::*> {
       using member_type = U;
};



template <typename...> struct arg_1
//{using type =void;}
;
 
/*
template <typename R, typename A, typename... Args>
struct arg_1<R(A, Args...)>
{
        using type = A;
};


template <typename R, typename A, typename... Args>
struct arg_1<R(A, Args...)const>
{
         using type = A;
};


template <typename Ret, typename Cls, typename T, typename... Args>
struct arg_1<Ret (Cls::*)(T, Args...)> {
    using type = T;
};

 
template <typename T>
using arg_1_t =  typename arg_1<T>::type;   ///error here: no arg 1 recognized

*/

/////////////////

template <typename...> struct ret
//{using type =void;}
;
 
template <typename R,  typename... Args>
struct ret<R( Args...)>
{
        using type = R;
};

template <typename R,  typename... Args>
struct ret<R(Args...)const>
{
         using type = R;
};

template <typename Ret, typename Cls,  typename... Args>
struct ret<Ret (Cls::*)(Args...)> {
    using type = Ret;
};
 
template <typename T>
using ret_t =  typename ret<T>::type;   ///error here: ???

