#pragma once

#include <foab.hpp>
#include <util/optional_type.hpp>
#include <util/offtype.hpp>
#include <xtypes.hpp>
#include <cassert>

namespace stepworks {

using stepworks::types::var_t;

template<typename...> struct f2f;


template<typename Ta, typename Tb>
struct f2f<Tb(const Ta&)>{
    using F = Tb(const Ta);
     F _f;
    auto f1(const Ta& a)->Tb{
        return f(a);
    }
};

/*
template <typename Form>
struct f2f  {
    template  <typename Ta, typename Tb>
    struct fab {
        using F1 =Tb(*)(const Ta&);
        F1 _f1;
        using F0 =Tb(*)();
        F0 _f0;

        auto f1(Ta&& a) {
            assert(_f1);
            return _f1(std::move(a));
        }
        auto fo() {
            assert(_f0);
            return _f0();
        }
    }
};


}



template<typename Ta, typename Tb, template<typename> typename Form = var_t>
struct foab2fab< Tb(const Ta&)> {

};

template<typename Ta, typename Tb, template<typename> typename Form = var_t>
struct foab2fab< Tb(const Ta&) const> {

};
*/

}
