#pragma once

#include "apply_function.hpp"
#include <core/optional.hpp>
#include <rw/wforward.hpp>

using stepworks::types::var_t;

using stepworks::types::var_type;

namespace stepworks::application {

    
    
    
//simple
    //function
template <
    typename Ta,
    typename  Tb, template <typename ...> typename Writer>
struct apply< Writer<Tb>,Tb(*)(const Ta&) > {
    using F = Tb(*)(const Ta&);
    F _f;


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

};

////
    //type     .... 
/*  
template <
    typename Ta,
    template <typename ...> typename Writer>
struct apply< Writer<Ta>&&> {
    //Writer deconstructiv : W
    Writer<Ta>&& _w;
    
    template <template <typename ...> typename Reader>
    constexpr Writer<Ta>  operator()( Reader<Ta, var_t<Ta>>&& r ) const {
        auto ra = _go_(r);
        return (ra.second) ?
        
        apply{ _w(*ra.second)  }  ( ra.first)  :
               std::move(_w);
    }

    template <template <typename ...> typename Reader,  template<typename, typename >typename  Form, typename Else >
    constexpr  Writer<Ta>  operator()( Reader<Ta, Form<Ta,Else>>&& r )const  {
        auto ra = _go_(r);
        struct vis {

            const apply& _here;
            auto operator()(const Ta&a, Reader<Ta, Form<Ta, Else>>&& r )const {
                return  apply{   _here._w (a) }( r );
            }
            auto operator()(const Else&a, Reader<Ta, Form<Ta, Else>>&& r)const {

                return    std::move(  _here._w) ;
            }
        };
        return std::visit(vis {*this}, ra.second,ra.first, _w);
    }

};


template <typename Ta,template <typename> typename  Writer>
auto _(Writer<Ta>&& dest){
    return apply< Writer<Ta>&& >{ std::move(dest) };
}
*/


//with predicate


template <
    typename Ta,
    typename  Tb, template <typename ...> typename Writer>
struct apply< Writer<Tb>,Tb(*)(const Ta&), bool(const Ta&)> {
    using F = Tb(*)(const Ta&);
    F _f;
    bool (*fpredicate) (const Ta&);

    template <template <typename ...> typename Reader>
    constexpr Writer<Tb>  operator()( Reader<Ta, var_t<Ta>>&& r, Writer<Tb>&& w  ) const {
        auto ra = _go_(r);
        return _go_   (ra.second) ?   apply( std::move(ra.first),  _go_(w, ra.second, fpredicate))
               :
               std::move(w);
    }

    template <template <typename ...> typename Reader,  template<typename, typename >typename  Form, typename Else >
    constexpr Writer<Tb>  operator()( Reader<Ta, Form<Ta,Else>>&& r, Writer<Tb>&& w  ) const {
        auto ra = _go_(r);
        struct vis {

            const apply& _here;
            auto operator()(const Ta&a, Reader<Ta, Form<Ta, Else>>&& r, Writer<Tb>&& w )const {

                //return  apply{ _here._f } ( std::move( a) , std::move(w));
                return apply ( std::move(r),  _go_(w, a,  _here.fpredicate)) ;

            }
            auto operator()(const Else&a, Reader<Ta, Form<Ta, Else>>&& r, Writer<Tb>&& w)const {

                return    std::move(w) ;
            }
        };
        return std::visit(vis {*this}, ra.second,ra.first, w);
    }
};

template<typename Ta,         
         template <typename ...>typename  Dest,
         typename  Stream 
         //, template <typename > typename Form = var_t
         >
struct apply <Ta, Stream, Dest<Ta>> {
    Stream &&  _ist;
    //Dest<Ta>&&  _dest;
    auto operator()(Dest<Ta> &&  d)  ->Dest<Ta>{
        if (_ist.bad())
            return std::move(d);
        Ta a;
        _ist>> a;
        if (_ist.fail())
            return std::move(d);
        else
            return apply{ std::move(_ist) }(std::move(d.f1(a)) ) ;   
    }
};



}
