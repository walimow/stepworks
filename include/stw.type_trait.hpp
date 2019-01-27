#pragma once

#include  <type_traits>
#include <utility>

#include <xtypes.hpp>
#include <xt.hpp>
#include <util/argtype.hpp>  //PM_traits

//using  stepworks::types::xT;

namespace stepworks{

///////////////////// reader
    
//  r->ra    
template <typename...> struct is_r_morph;

template <typename...> 
struct is_r_morph : std::false_type {};

template <typename R, typename T > 
struct is_r_morph< std::pair<R,T>(R&&) > : std::true_type {};

//as member
template <typename Cls, typename R, typename T > 
struct is_r_morph<std::pair<R,T> (Cls::*)(R&&)> : std::true_type {};

template <typename Cls, typename R, typename T > 
struct is_r_morph<std::pair<R,T> (Cls::*)(R&&)const > : std::true_type {};



//  r->r(a)
template <typename...> struct is_r0_morph;

template <typename...> 
struct is_r0_morph : std::false_type {};

template <typename R, typename T , template  <typename> typename Form > 
struct is_r0_morph< std::pair<R, Form< T> >(R&&) > : std::true_type {};

//as member
template <typename Cls, typename R, typename T , template  <typename> typename Form > 
struct is_r_morph<std::pair<R,Form< T> > (Cls::*)(R&&)> : std::true_type {};

template <typename Cls, typename R, typename T , template  <typename> typename Form > 
struct is_r_morph<std::pair<R,Form< T> > (Cls::*)(R&&)const > : std::true_type {};    


  
//  r->(r)(a)
template <typename...> struct is_r00_morph;

template <typename...> 
struct is_r00_morph : std::false_type {};

template <typename R, typename T , template  <typename> typename FormR > 
struct is_r00_morph< std::pair<FormR<R>, FormR< T> >(R&&) > : std::true_type {};


//  (r)->(r)(a)
template <typename...> struct is_rx0_morph;

template <typename...> 
struct is_rx0_morph : std::false_type {};

template <typename R, typename T , template  <typename> typename FormR, template  <typename> typename FormA > 
struct is_rx0_morph< std::pair<FormR<R>, FormA< T> >(R&&) > : std::true_type {};


//as member
template <typename Cls, typename R, typename T , template  <typename> typename FormR, template  <typename> typename FormA  > 
struct is_r_morph<std::pair<FormR< R>,FormA< T> > (Cls::*)(R&&)> : std::true_type {};

template <typename Cls, typename R, typename T , template  <typename> typename FormR, template  <typename> typename FormA  > 
struct is_r_morph<std::pair<FormR< R>,FormA< T> > (Cls::*)(R&&)const > : std::true_type {};    


///////////////////// writer

// w,a->w
template <typename...> struct is_w_morph;

template <typename...> 
struct is_w_morph : std::false_type {};

template <typename W, typename T > 
struct is_w_morph< W(W&&, const T&) > : std::true_type {};

template <typename Cls, typename W, typename T > 
struct is_w_morph< W(Cls::*)( W&&, const T&) > : std::true_type {};

template <typename Cls, typename W, typename T > 
struct is_w_morph< W(Cls::*)( W&&, const T&) const> : std::true_type {};


// w,(a)->w
template <typename...> struct is_w0_morph;

template <typename...> 
struct is_w0_morph : std::false_type {};

template <typename W, typename T, template <typename> typename Form  > 
struct is_w0_morph< W(W&&, const Form<T>&) > : std::true_type {};

template <typename Cls, typename W, typename T, template <typename> typename Form  > 
struct is_w0_morph< W(Cls::*)(W&&, const Form<T>&) > : std::true_type {};

template <typename Cls, typename W, typename T, template <typename> typename Form  > 
struct is_w0_morph< W(Cls::*)(W&&, const Form<T>&) const > : std::true_type {};


// w,(a)->(w)  //p.e.: for asynchronity
template <typename...> struct is_w0x_morph;

template <typename...> 
struct is_w0x_morph : std::false_type {};

template <typename W, typename T, template <typename> typename FormW, template <typename>  typename Form  > 
struct is_w0x_morph< FormW<W>(W&&, const Form<T>&) > : std::true_type {};

template <typename Cls,typename W, typename T, template <typename> typename FormW, template <typename>  typename Form  > 
struct is_w0x_morph< FormW<W>(Cls::*)(W&&, const Form<T>&) > : std::true_type {};

template <typename Cls,typename W, typename T, template <typename> typename FormW, template <typename>  typename Form  > 
struct is_w0x_morph< FormW<W>(Cls::*)(W&&, const Form<T>&) const > : std::true_type {};

    
}
