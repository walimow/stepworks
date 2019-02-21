
#pragma once


#include <util/optional_type.hpp>

#include <type_traits>
//#include  <utility>

using stepworks::types::var_t;

namespace stepworks::application {


template <typename T, typename = void>
struct has_member_f0
    : std::false_type
{};

template <typename T>
struct has_member_f0<T,
       std::void_t<decltype(std::declval<T>().f0())>>
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




///f-struct

template <typename Ta, typename F, typename R  /* = typename F::_return_type*/ >
struct apply <Ta,F,R> {
    const F& _f;

    constexpr auto operator()(const Ta& a)->R {
        return _f.f1(a);
    }

    constexpr auto operator()(const var_t<Ta>& a0)->R {
        if (a0) {
            if constexpr(has_member_ft<F>()) {
                return _f._ft(*a0);
            }
            else if constexpr(has_member_f0<F>()) {
                return _f._f0(*a0);
            }
            else
                _f(*a0);
        }
        else {
            if constexpr(has_member_f0<F>()) {
                return _f._f0();
            }
            else
               return  _f(*a0);
        }
    }

    template < template <typename,typename > typename Form,  typename Else>
    constexpr auto operator ()(const Form<Else,Ta>& a0) {
        struct v {
            const apply here;
            constexpr auto operator()(const Ta&a)const {
                if constexpr(has_member_ft<F>()) {
                    return here._f._ft(a);
                }
                else if constexpr(has_member_f0<F>()) {
                    return here._f._f0(a);
                }
                else
                    here._f(a);
            }

            constexpr auto operator()(const Else&a)const {
                if constexpr(has_member_ft<F>( )) {
                    return here._f._ft(a);
                }
                if constexpr(has_member_f0<F>()) {
                    return here._f._f0();
                }
                else
                   return  here._f(a);
            }
        };
        return    std::visit(v{*this },   a0 );
    };

};




}
