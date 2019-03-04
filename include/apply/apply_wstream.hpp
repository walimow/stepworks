#pragma once

#include  "apply_abstact.hpp"

namespace stepworks{
    
    
//simple
    //function
template <
    typename Ta,
     template <typename ...> typename Writer
    ,template <typename ...> typename Form 
    >
struct apply<F, Form<> > {
    
    F _f;
    
    constexpr Writer<Tb>  operator()( Reader<Ta, var_t<Ta>>&& r, Writer<Tb>&& w  ) const {
        auto ra = _go_(r);
        return (ra.second) ?   apply{ _f } ( std::move( *ra.second),   _go_ (  std::move(w)) )  :
               std::move(w);

    }


/*
    template <template <typename ...> typename Reader>
    constexpr Writer<Tb>  operator()( Reader<Ta, var_t<Ta>>&& r, Writer<Tb>&& w  ) const {
        auto ra = _go_(r);
        return (ra.second) ?   apply{ _f } ( std::move( *ra.second),   _go_ (  std::move(w)) )  :
               std::move(w);

    }

    template <template <typename ...> typename Reader,  template<typename, typename >typename  Form, typename Else >
    constexpr  Writer<Tb>  operator()( Reader<Ta, Form<Ta,Else>>&& r, Writer<Tb>&& w  ) {
        auto ra = _go_(r);
        struct vis {

            const apply& _here;
            auto operator()(const Ta&a, Reader<Ta, Form<Ta, Else>>&& r, Writer<Tb>&& w )const {
                return  apply{ _here._f } ( std::move( a), std::move(w));
            }
            auto operator()(const Else&a, Reader<Ta, Form<Ta, Else>>&& r, Writer<Tb>&& w)const {

                return    std::move(w) ;
            }
        };
        return std::visit(vis {*this}, ra.second,ra.first, w);
    }
*/

};

    
}
