#include "gtest/gtest.h"
#include <eal/reader_state.hpp>


struct genmod{
    int _start=0;
    int _mod=5;
};

auto _(genmod&& r){
    auto a = r._start;
    return std::make_pair (genmod{ ++r._start % r._mod, r._mod  },  a);
}


TEST (reader_state_test, gen1_to_6 )
{
    auto [r,a] = _( genmod());
    std::cout<< "\na: "<< a<< " r: "<<r._start<<'\n';
    {
        auto [r1,a1] = _( std::move(r));
        std::cout<< "\na1: "<< a1<< " r1: "<<r._start<<'\n';
    }
}
