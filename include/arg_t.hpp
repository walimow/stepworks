#pragma once

#include <type_traits>

namespace argtool{
    
    
template <typename ...Args>
struct args_t{
    
};

template <size_t,  typename...> struct arg_t;

template < size_t N,   typename R, typename A , typename ...Args>
struct arg_t<N, R(A, Args...)>{
    using type = typename arg_t<N-1, R( Args...)>::type;
};

template < typename R, typename A , typename ...Args>
struct arg_t<0, R (A, Args...)>{
    using type =A;
};


template<typename R, typename =void>  struct is_ft1 : std::false_type {};

          

 template < template <typename...> typename T, typename A>
struct is_ft1<
            T<A>  ,
           std::void_t<        
                 decltype( std::declval<  T <A> >().operator() ( std::declval<A>())  )              
                 > 
           >:std::true_type{ };

           


template < template <typename> typename T ,   typename A>
struct arg_t<    0,   T<A>    >
{
    
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
