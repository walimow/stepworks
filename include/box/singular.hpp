//
// Created by karsten on 27.11.20.
//

#ifndef BOX_SINGULAR_HPP
#define BOX_SINGULAR_HPP

#include <utility>
#include <type_traits>
#include <def.hpp>
#include <detect/detect_iterable.hpp>

using stepworks::bxx::box;
using stepworks::bxx::detect::is_forward_iterable;

namespace stepworks::singular {


    ///to be replaced
    template<typename Ty>
    struct singular_t {
        Ty _value;

        singular_t() = delete;

        singular_t(Ty a) {
            _value = std::move(a);
        }

        singular_t(const singular_t<Ty> &) = delete;

        singular_t &operator=(const singular_t<Ty> &) = delete;

        singular_t &operator=(singular_t<Ty> &&) = default;

        singular_t(singular_t<Ty> &&) = default;
    };

    template<typename Ty>
    struct singular_t<Ty> mk_singular(Ty a) {
        return singular_t<Ty>(std::forward<Ty>(a));
    }

    template<typename Ty, typename ...Args>
    using fdc_t = Ty(*)(Ty, Args...);

    template<typename Ty, template<typename...> typename C, typename ...Args> requires(is_forward_iterable<C<Ty> >::value)
    auto  apply(   fdc_t<Ty, Args...> f, const C<Ty> &l,  singular_t<Ty> &&  a = singular_t < Ty > {0},Args ... args) {
    for ( const  auto& e    : l)
        a = f(std::move(a._value), e, args...);
    return std::move(a);
};

    ///???
template<typename F,  typename Ty, template<typename...> typename C, typename ...Args>
requires(        is_forward_iterable<C< box< Ty,C>  > >::value)
auto  apply(  F f, const C< box< Ty,C> > &l, singular_t<Ty> &&a = singular_t < Ty > {0}, Args... args)
{
for (const auto& e : l)
    a = f(std::move(a._value), e, args...);
return  std::move(a);
};

template<typename F,  typename Ty, template<typename...> typename C, typename ...Args>
//requires(        !is_iterable<C< box< Ty,C>  > >::value)
auto  apply(  F f, const  box< Ty,C > &a, singular_t<Ty> &&s = singular_t < Ty > {0}, Args... args)
{
      return  std::move(  f( a._value, std::move(s), args...));
};


template<typename F,  typename S, typename Ty, template<typename...> typename C, typename ...Args>
//requires(        !is_iterable<C< box< Ty,C>  > >::value)
auto  apply(  F f, const  box< Ty,C > &a, S &&s = S{0}, Args... args)
{
    return  std::move(  f( a._value, std::move(s), args...));
};


template<typename F, typename S,  typename Ty, template<typename...> typename C, typename ...Args>
requires(        is_forward_iterable<C< box< Ty,C>  > >::value)
auto  apply(  F f, const C< box< Ty,C> > &l, S &&a = S {0}, Args... args)
{
for (const auto& e : l)
a = f(std::move(a._value), e, args...);
return  std::move(a);
};


template<typename F, typename Ty, template<typename...> typename C>
//requires(    is_iterable<C< box< Ty,C> > >::value)
auto  apply(  F f,const C< box< Ty,C> > &l, singular_t< typename  F::data_t >&& a = singular_t <typename  F::data_t> {0})
{
for ( const auto& e: l)
    //a =
    f(std::move(a._value), e);
return std::move(a);
};


template <typename F, typename Ty, typename S , typename Q>
struct continuation {

    //decltype( F())
/*
    auto operator()( F f, Ty a, S&& s , continuation &cc ){
        auto rr = Q(f(a, std::move(s)))
        return rr ? <;  //=>s

    }
*/
};

/*
template <typename Ty, template <typename...> typename C,  typename ...Args>
requires (!is_iterable< C<Ty>   >::value)
auto  apply(
        fdc_t<Ty, Args...> f,
const C<Ty>& l,
        singular_t<Ty>&& a = singular_t<Ty>{ 0 },
        Args... args)
{
    a = f(std::move(a._value), args...);
    return std::move(a);
};
*/


template<typename Ty, typename ...Args>
auto apply(
        fdc_t<Ty, Args...> f,
        singular_t <Ty> &&a,
        Args... args) {
    a = f(std::move(a._value), args...);
    return std::move(a);
};


template<typename Ty, typename ...Args>
auto apply(
        fdc_t<Ty, Args...> f,
        Ty &&a,
        Args... args) {
    a = f(std::move(a), args...);
    return std::move(a);
};


template<typename Ty, template<typename...> typename C>
auto apply(
        fdc_t <Ty, Ty> f,
        const C<Ty> &l,
        singular_t <Ty> &&a = singular_t < Ty > {0}) {
    for (auto e : l)
        a = f(std::move(a._value), e);
    return std::move(a);
};

struct _iteration_t;  ///pseudorecurs

//singular context function applicator

template<typename Ty, typename single_context_t, typename function_t>
struct _sfx {
///type_traits:
    ///bool : valid
    /// iterable

    ///  construction: function_t, single_context_t -> fx_t
    using fx_t = std::pair<function_t, single_context_t>;

    static auto mk_fx(function_t ft, single_context_t scx) {
        return std::make_pair(std::move(ft), std::move(scx));

    }

    ///  application: ft_t, Ty ->fx_t
    /// writimg
    fx_t fapp(fx_t &&f, Ty a) {
        auto cx = std::move(f.second);
        return std::move(f)(std::move(a));
    };

    ///   destruction (to product) fx_t -> single_context_t
    static auto destruct_production(fx_t x) {
        return std::move(x.second);
    }


    /// requirements for iterativ scx
    struct _iteration_t {
        // single_context&&()->single_context
        static single_context_t _step(single_context_t &&scx) {
            return scx();
        }

        static bool is_valid(const single_context_t &scx) {
            return (bool) scx;
        }
    };

};

}

#endif //BOX_SINGULAR_HPP
