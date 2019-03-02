
#pragma once



#include <core/optional_type.hpp>

#include <core/ftypetraits.hpp>

#include "apply_abstact.hpp"

using stepworks::types::var_t;


using stepworks::has_member_f0;
using stepworks::has_member_f1t;
using stepworks::has_member_ft;


namespace stepworks::application {


///f-struct

template <typename Ta, typename F, typename R  /* = typename F::_return_type*/ >
struct apply <Ta,F,R> {
    const F& _f;

    constexpr auto operator()(const Ta& a)->R {
        return _f.f1(a);
    }

    
    constexpr auto operator()(const var_t<Ta>& a0)->R {
        if (!a0) {
            if constexpr(has_member_ft<F>()) {
                return _f.ft(*a0);  //??
            }
            else if constexpr(has_member_f0<F>()) {
                return _f.f0();
            }
        }
        else {
            if constexpr(has_member_f1t<F,Ta>()) {
                return _f.f1(*a0);
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
                    return here._f.f0(a);
                }
                else
                    here._f(a);
            }

            constexpr auto operator()(const Else&a)const {
                if constexpr(has_member_ft<F>( )) {
                    return here._f._ft(a);
                }
                if constexpr(has_member_f0<F>()) {
                    return here._f.f0();
                }
                else
                   return  here._f(a);
            }
        };
        return    std::visit(v{*this },   a0 );
    };

};




}
