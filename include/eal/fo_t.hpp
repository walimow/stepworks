#pragma  once

#include <type_traits>
#include <util/testvoid.hpp>
#include <util/function_traits.hpp>

namespace stepworks::eal::fo {

    
    
template< class , class =void>
struct has_signature_t:  std::false_type{};

template <class T>
struct has_signature_t<T, typename test_void< typename T::arg_signature_tt>::type>  : std::true_type{};


///build function objects

template <typename ...> struct ft;

template < typename R, typename ...Args>
struct ft<R,Args...> {
    using F = R(*)(Args...);

    F _f;

    auto operator()(Args&&...args) noexcept {
        return _f(args...);
    }
    using arg_signature_tt = std::tuple<Args...>;
    auto operator()(arg_signature_tt args) {
        assert(_f);
        return  std::apply(	_f	,	args);
    }
};



template <typename ClassType, typename ReturnType, typename... Args>
struct ft<ReturnType(ClassType::*)(Args...) const> {
    
    using ptr_type =ReturnType(ClassType::*)(Args...) const;
    using arg_signature_tt = std::tuple<Args...>;
    
    ptr_type _f;
  //  ReturnType *_f (ClassType::*)(Args...) ;
    

    auto operator()(Args&&...args) noexcept {
        return _f(args...);
    }
    
     auto operator()(arg_signature_tt args) {
        assert(_f);
        return  std::apply(	_f	,	args);
    }    
};


template <typename ClassType, typename ReturnType, typename... Args>
struct ft<ReturnType(ClassType::*)(Args...) > {
    
    using ptr_type =ReturnType(ClassType::*)(Args...) ;
    using arg_signature_tt = std::tuple<Args...>;
    
    ptr_type _f;
  //  ReturnType *_f (ClassType::*)(Args...) ;
    

    auto operator()(Args&&...args) noexcept {
        return _f(args...);
    }
    
     auto operator()(arg_signature_tt args) {
        assert(_f);
        return  std::apply(	_f	,	args);
    }    
};


//<decltype(&T::operator()


template < typename R, typename ...Args>
struct ft<R(Args...)> {
    using F = R(*)(Args...);

    F _f;

    auto operator()(Args&&...args) noexcept {
        return _f(args...);
    }
    using arg_signature_tt = std::tuple<Args...>;
    auto operator()(arg_signature_tt args) {
        assert(_f);
        return  std::apply(	_f	,	args);
    }
};

template <typename F, typename... Args>
struct _L{
    F&& _f;
    using arg_signature_tt = std::tuple<Args...>;
};



template <typename F>
struct ft<F, typename std::enable_if< 
has_signature_t<F>::value>::type  
>
{
    F&& _f;
    template <typename ...Args>
    auto operator() (Args&&...args) noexcept {
        return _f(args...);
    }
    using arg_signature_tt = typename F::arg_signature_tt;
    
    auto operator()(arg_signature_tt&& args_tuple) {
        return  std::apply( _f  ,
                    args_tuple);
    }
};



template <typename F>
struct ft<F, typename std::enable_if< !has_signature_t<F>::value>::type  >
{
  //  static_assert(false);
    F&& _f;
    template <typename ...Args>
    auto operator() (Args&&...args) noexcept {
        return _f(args...);
    }
    using arg_signature_tt = typename  function_traits<F>::tuple_type;; 
    
    auto operator()(arg_signature_tt&& args_tuple) {
        return  std::apply( _f  ,
                    args_tuple);
    }
    
};


template <typename F, typename Signature>
struct ft<F, Signature>
{
  //  static_assert(false);
    F&& _f;
    template <typename ...Args>
    auto operator() (Args&&...args) noexcept {
        return _f(args...);
    }
    using arg_signature_tt = Signature; 
    
    auto operator()(arg_signature_tt&& args_tuple) {
        return  std::apply( _f  ,
                    args_tuple);
    }
    
};



//////////////////////
template <typename F, typename Enable = void>
struct _ft;


template <typename F>
struct _ft<F, typename std::enable_if< !has_signature_t<F>::value>::type  >
{
    F&& _f;
    template <typename ...Args>
    auto operator() (Args&&...args) noexcept {
        return _f(args...);
    }
    using arg_signature_tt = typename  function_traits<F>::tuple_type;
    
    auto operator()(arg_signature_tt&& args_tuple) {
        return  std::apply( _f  ,
                    args_tuple);
    }
    
};

template <typename F>
struct _ft<F, typename std::enable_if< 
has_signature_t<F>::value>::type  
>
{
    F&& _f;
    template <typename ...Args>
    auto operator() (Args&&...args) noexcept {
        return _f(args...);
    }
    using arg_signature_tt = typename F::arg_signature_tt;
    
    auto operator()(arg_signature_tt&& args_tuple) {
        return  std::apply( _f  ,
                    args_tuple);
    }
};


struct factor
{
    template <typename F >// ,  typename std::enable_if< ! has_signature_t< F >::value>::type >
    constexpr static  auto gen( F f ) noexcept {
        return  ft< F, typename  function_traits<F>::tuple_type> { std::move(f)} ;
    }

    template < typename F,  typename std::enable_if< has_signature_t<F>::value>::type >
    constexpr static  auto gen( F&& f ) noexcept {
        return  ft< F > { std::move( f) } ;
    }
    
    template < typename R,  typename ...Args>
    constexpr  static auto gen( R(*f)(Args...) ) noexcept {
        return  ft< R,Args...> {f} ;
    }
 
};



}
