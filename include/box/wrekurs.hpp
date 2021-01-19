//
// Created by kh on 01.12.20.
//

#ifndef BOX_WREKURS_HPP
#define BOX_WREKURS_HPP

#include <utility>
#include <detect/detect_iterable.hpp>
#include <iostream>

using stepworks::detect::is_forward_iterable;

///handles problems with continuos operation to potentially singular (result) 'writing' types (filehandles etc)

///todo(?) adaption f(A,B)->B   => (writing_f_t) f(const A&, const B&&)->B

namespace stepworks {


template<typename F, typename Iterable_t,
        typename W //typename F::return_t
        //=decltype( std::declval<F>()(   *std::declval<Iterable_t>().begin()  ,  *std::declval<Iterable_t>().begin()   ) )
        , typename ...Arguments
> requires(is_forward_iterable<Iterable_t>::value)
auto apply_iterativ_continuation( const F& f,
                                  //const
                                  W w, const Iterable_t &it_t,  typename Iterable_t::const_iterator it, Arguments...args )-> W{
    return
     it == it_t.end() ?

       std::move(w)   //std::forward<W&&>(w)

    :
    apply_iterativ_continuation(   f,
                                   f(*it, std::forward<
            //const
            W&&>(w) ) , it_t, ++it   ) ;
}

template<typename F , typename Iterable_t
        , typename W= decltype( std::declval<F>()(   *std::declval<Iterable_t>().begin()  ,  *std::declval<Iterable_t>().begin()   ) )
        > requires(is_forward_iterable<Iterable_t>::value)
auto iterativ_continuation( const F& f, const Iterable_t &it_t,
                            //const
                            W&& r = W{0}
)->W
{
typename Iterable_t::const_iterator it=it_t.begin();
return  apply_iterativ_continuation( f, std::move( r), it_t, it);
}


///variable arguments,  implicit initialisation of r
template<typename F , typename Iterable_t
        , typename W =  typename F::return_t
        , typename ...Arguments
> requires(is_forward_iterable<Iterable_t>::value)
auto iterativ_continuation( const F& f, const Iterable_t &it_t, Arguments...args
)->W
{
 //const
 W&& w = W{};
typename Iterable_t::const_iterator it=it_t.begin();
return  apply_iterativ_continuation( f, std::move( w), it_t, it);
}

///variable arguments, explicit initialisation of r
template<typename F , typename Iterable_t
        , typename W //= decltype( std::declval<F>()(   *std::declval<Iterable_t>().begin()  ,  *std::declval<Iterable_t>().begin()   ) )
        , typename ...Arguments
> requires(is_forward_iterable<Iterable_t>::value)
auto iterativ_continuation( const F& f, const Iterable_t &it_t, W&& w, Arguments...args
)->W
{
typename Iterable_t::const_iterator it=it_t.begin();
return  apply_iterativ_continuation( f, std::move( w), it_t, it);
}


}


#endif //BOX_WREKURS_HPP
