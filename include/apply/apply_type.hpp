
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


template <typename F >
struct apply <const F&> {
//struct apply <Ta,F,R> {
    const F& _f;
    template<typename  Ta >
    constexpr auto operator()(const Ta& a) {
        if constexpr(has_operator_t<F, decltype( a )>())
               return _f(a);
        else
          if constexpr(has_member_f1t<F,Ta>()) 
                  return _f.f1(a);
          else
              assert(false); //unhandled!  //todo: static
    }
    template<typename  Ta>
    constexpr auto operator()(const var_t<Ta>& a0) {
        /*
         has_operator_t<T,Arg,
         */
        {
           if constexpr(has_operator_t<F, decltype( a0 )>())
               return _f(a0);
        //   else
        //       static_assert(  (has_member_ft<F>()) || (has_member_f0<F>() )  );   //no f0 defined for uncertain type
        }
        
        bool test = (bool)(a0);
        if (!test) {
            if constexpr(has_member_ft<F>()) {
                return _f.ft(*a0);  //??
            }
            else   if constexpr(has_member_f0<F>()) {
                return _f.f0();
            }
        }
        else {
            if constexpr(has_member_f1t<F,Ta>()) {
                return _f.f1(*a0);
            }
            else
            //    if constexpr(has_operator_t<F,Ta>())
                    return _f(*a0);
       
        }
      /*static_*/assert(false)  ;
    }

    template < typename Ta, template <typename...> typename Form,  typename Else>
    constexpr auto operator ()(const Form<Else,Ta>& a0) {
        {
            static_assert(  (has_member_ft<F>()) || (has_member_f0<F>() )  );
        }
        struct v {
            const apply& here;
            constexpr auto operator()(const Ta&a)const {
                if constexpr(has_member_f1t<F,Ta>()) {
                    return here._f.f1(a);
                }
            /*    else if constexpr(has_member_f0<F>()) {
                    return here._f.f0();
                }*/
                else  
                    //*/
                   return here._f(a);
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


template <typename Fa>
auto _(const Fa& foab) {
    return apply< const Fa&> { foab };
}

///////////



//namespace nn{
//template <typename...> struct apply;    
    
template <template <typename> typename Ft , typename Ty >
struct apply <const Ft<Ty>&> {
    const Ft<Ty>& _f;

    using F = Ft<Ty>;

    template<typename  Ta >
    constexpr auto operator()(const Ta& a) {
        return _f.f1(a);
    }
    template<typename  Ta>
    constexpr auto operator()(const var_t<Ta>& a0) {
        {
            static_assert(  (has_member_ft<F>()) || (has_member_f0<F>() )  );   //no f0 defined for uncertain type
        }
        bool test = (bool)(a0);
        if (!test) {
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

    template < typename Ta, template <typename...> typename Form,  typename Else>
    constexpr auto operator ()(const Form<Else,Ta>& a0) {
        {
            static_assert(  (has_member_ft<F>()) || (has_member_f0<F>() )  );
        }
        struct v {
            const apply& here;
            constexpr auto operator()(const Ta&a)const {
                if constexpr(has_member_f1t<F,Ta>()) {
                    return here._f.f1(a);
                }
                else
                    here._f(a);
            }

            constexpr auto operator()(const Else&a)const {
                if constexpr(has_member_ft<F>( )) {
                    return here._f.ft(a);
                }
                if constexpr(has_member_f0<F>()) {
                    return here._f.f0();
                }
                else
                    return  here.f(a);
            }
        };
        return    std::visit(v{*this },   a0 );
    };
};
//}

template <template <typename> typename F, typename Ty>
auto _( const F<Ty>& foab) {
    return apply< const F<Ty>&> { foab };
}

////
/**
 *   rref-Foab could no be distinuished from writer
 */

template <template <typename> typename Ft , typename Ty >
struct apply < Ft<Ty>&&> {
    const Ft<Ty>&& _f;

    using F = Ft<Ty>;

    template<typename  Ta >
    constexpr auto operator()(const Ta& a) {
        return _f.f1(a);
    }
    template<typename  Ta>
    constexpr auto operator()(const var_t<Ta>& a0) {
        {
            static_assert(  (has_member_ft<F>()) || (has_member_f0<F>() )  );   //no f0 defined for uncertain type
        }
        bool test = (bool)(a0);
        if (!test) {
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

    template < typename Ta, template <typename...> typename Form,  typename Else>
    constexpr auto operator ()(const Form<Else,Ta>& a0) {
        {
            static_assert(  (has_member_ft<F>()) || (has_member_f0<F>() )  );
        }
        struct v {
            const apply& here;
            constexpr auto operator()(const Ta&a)const {
                if constexpr(has_member_f1t<F,Ta>()) {
                    return here._f.f1(a);
                }
             /*   else if constexpr(has_member_f0<F>()) {
                    return here._f.f0();
                }
                else*/
                 return    here._f(a);
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
//}

template <template <typename> typename F, typename Ty>
auto _x( F<Ty>&& foab) {
    return apply< F<Ty>&&> { std::move( foab) };
}



/*
template <template <typename> typename F, typename Ty>
auto _(  F<Ty>&& foab) {
    return apply< const F<Ty>&> { std::move(foab) };
}
*/

/*
template <typename F >
struct apply <F&&> {

    F&& _f;

    template<typename  Ta >
    constexpr auto operator()(const Ta& a) {
        return std::move(_f).f1(a);
    }
    template<typename  Ta>
    constexpr auto operator()(const var_t<Ta>& a0) {
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

    template < typename Ta, template <typename,typename > typename Form,  typename Else>
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


template <typename F>
auto _( F&& foab) {
    return apply< F&&> { foab };
}

*/



}
