#include "util/log.hpp"

//using stepworks::types::var_tx;
#include <iostream>
#include <vector>

#include <box/box.hpp>
#include <box/apply.hpp>
/*
using stepworks::bxx::apply;
//using stepworks::bxx::apply_f;


template <typename Ty>
struct s_print{

    using value_t= Ty;

    auto operator()(const Ty& a, value_t && x )const{
     std::cout<< a << "  ";
        return std::move(++x);
    }
};

 */

int main(){
    int rc=0;
/*
    using stepworks::bxx::box;

    using v_T= double;

    using T_t =box<  v_T , std::vector>;

    auto u=T_t {1.,2.};

    auto v=T_t  {11.,
               T_t    {2., 3.,42.} ,
               44.9};

    int rc = apply_f(v, s_print<int>{}, 0);

    rc = apply_f( v, s_print<int>{},0);
*/
    return rc;


}
