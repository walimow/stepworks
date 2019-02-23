#pragma once

#include "apply_function.hpp"
#include <util/optional.hpp>

using stepworks::types::var_t;

using stepworks::types::var_type;

//simple

template <
//        template <typename > typename Form,
//        typename Ta, template <typename ...> typename Reader, 
   typename Ta,
        typename  Tb, template <typename ...> typename Writer>
struct apply< Writer<Tb>,Tb(*)(const Ta&) > {
    using F = Tb(*)(const Ta&);
    F _f;
    
    
    Writer<Tb>  operator()( Reader<Ta, var_t>&& r, Writer<Tb>&& w  ) {
        auto ra = _go_(r);
        return (ra.second) ?  apply( _go_   std::move(w),   )
        
    }
    
    
    
    
    /*

      template  < template <typename...> typename Form>      ///clang-problem
  //  template  < template <typename,typename> typename Form>
    constexpr auto operator()(const Form<Else,A>& a0)const {
        struct vis {
            const apply& _here;
            auto operator()(const A&a)const {
                return _here._f(a);
            }
            auto operator()(const Else&a)const {

                return  _here._else(a);
            }
        };
        return std::visit(vis {*this}, a0);
    };
    */
};
