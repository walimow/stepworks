#pragma  once

#include <type_traits>
#include <util/testvoid.hpp>
#include <util/function_traits.hpp>
#include "util_t.hpp"

namespace stepworks::eal::fo {

using stepworks::eal::_sz_;    
    
template< class , class =void>
struct has_signature_t:  std::false_type{};

template <class T>
struct has_signature_t<T, typename test_void< typename T::arg_signature_tt>::type>  : std::true_type{};

/*

namespace detail {
template<typename T, std::size_t... Is>
auto constexpr tuple_from_array(T const& arr, std::index_sequence<Is...>)
{
  return std::make_tuple(arr[Is]...);
}

template<std::size_t N, typename V, typename T, std::size_t ...Is>
auto constexpr array_from_container(T const& c, std::index_sequence<Is...>)
{
  return std::array<V, N>{c[Is]...};
}

} // ns detail



template<typename T>
auto constexpr tuple_from_array(T const& arr)
{
  auto constexpr tup_size = std::tuple_size<std::decay_t<T>>::value;
  return detail::tuple_from_array(arr, std::make_index_sequence<tup_size>{});
}

template<typename T, std::size_t N>
auto constexpr tuple_from_array(T const (&arr)[N])
{
  return detail::tuple_from_array(arr, std::make_index_sequence<N>{});
}

// not safe
template<std::size_t N, typename T>
auto constexpr tuple_from_container(T const& c)
{
  using V = typename T::value_type;
  return tuple_from_array(detail::array_from_container<N, V>(c, std::make_index_sequence<N>{}));
}

*/


///build function objects

template <typename ...> struct ft;

template < typename R, typename ...Args>
struct ft<R,Args...> {
    using F = R(*)(Args...);

    static const std::size_t arg_sz= _sz_<Args...>::value;
    
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


template < typename F ,typename R ,typename ...Args>
struct ft<F, R, std::tuple<Args...>> {
    //using F = R(*)(Args...);

    static const std::size_t arg_sz= _sz_<Args...>::value;
    
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
    static const std::size_t arg_sz= _sz_<Args...>::value;

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
    
    static const std::size_t arg_sz= _sz_<Args...>::value;
    ptr_type _f;
  
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
    
    static const std::size_t arg_sz= _sz_<Args...>::value;

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
    
    static const std::size_t arg_sz= std::tuple_size(  std::declval<arg_signature_tt>());
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
    static const std::size_t arg_sz= std::tuple_size(  std::declval<arg_signature_tt>());
};


template <typename F, typename Signature>
struct ft<F, Signature>
{
    F _f;
    template <typename ...Args>
    auto operator() (Args&&...args) noexcept {
        return _f(args...);
    }
    using arg_signature_tt = Signature; 
    
    auto operator()(arg_signature_tt&& args_tuple) {
        return  std::apply( _f  ,
                    args_tuple);
    }
    static const std::size_t arg_sz= _sz_< Signature>::value;   ///TEST
};

template <typename F, typename Ta, typename ...RestArgs>
struct ft<F, std::tuple<Ta,RestArgs...>>
{
    F&& _f;
    template <typename ...Args>
    auto operator() (Args&&...args) noexcept {
        return _f(args...);
    }
    using arg_signature_tt = std::tuple<Ta,RestArgs...>; 
    
    auto operator()(arg_signature_tt&& args_tuple) {
        return  std::apply( _f  ,
                    args_tuple);
    }
    static const std::size_t arg_sz=  _sz_<  arg_signature_tt >::value;   ///TEST
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
    
    template < typename F
    //,  typename std::enable_if< has_signature_t<F>::value>::type  
    >
    constexpr static  auto gen_ts( F&& f ) noexcept {
        return  ft< F,   typename  F::arg_signature_tt > { std::move( f) } ;
    }
    
    template < typename R,  typename ...Args>
    constexpr  static auto gen( R(*f)(Args...) ) noexcept {
        return  ft< R,Args...> { f } ;
    }
 
};



}
