#pragma once

namespace argtool{

template <size_t,  typename...> struct arg_t;

template < size_t N,   typename R, typename A , typename ...Args>
struct arg_t<N, R(A, Args...)>{
    using type = typename arg_t<N-1, R( Args...)>::type;
};

template < typename R, typename A , typename ...Args>
struct arg_t<0, R (A, Args...)>{
    using type =A;
};



template < size_t N,   typename R, typename A , typename ...Args>
struct arg_t<N, R(A, Args...)const>{
    using type = typename arg_t<N-1, R( Args...)>::type;
};

template < typename R, typename A , typename ...Args>
struct arg_t<0, R (A, Args...)const >{
    using type =A;
};


template < size_t N, typename Cls,  typename R, typename A , typename ...Args>
struct arg_t<N, R(Cls::*)(A, Args...)>{
    using type = typename arg_t<N-1, R(Cls::*)( Args...)>::type;
};

template < typename Cls,typename R, typename A , typename ...Args>
struct arg_t<0, R (Cls::*)(A, Args...)>{
    using type =A;
};

template < size_t N,   typename Cls,typename R, typename A , typename ...Args>
struct arg_t<N, R (Cls::*)(A, Args...)const>{
    using type = typename arg_t<N-1, R(Cls::*)( Args...)>::type;
};

template < typename Cls,typename R, typename A , typename ...Args>
struct arg_t<0, R (Cls::*)(A, Args...)const >{
    using type =A;
};

template <typename T>
using arg_1_t =  typename arg_t<0, T>::type;   ///error here: no arg 1 recognized

}
