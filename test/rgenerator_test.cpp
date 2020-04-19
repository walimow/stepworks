#include "gtest/gtest.h"
#include <rw/rgenerator.hpp>
#include <process/proc.hpp>
#include <rw/wforward.hpp>
#include <list>
#include <vector>
#include <forward_list>
#include <util/ignore.hpp>

//using Frr = Ta(*)(Ta&&);

int gen_plus_nine(int&& x) {
    return x+9;
}

bool control_less_then_100(const int& x, void*) {
    return x<100;
}


TEST ( generator_test, first )
{
    auto g = stepworks::make_generator<int>(gen_plus_nine);
    stepworks::ignore(g);



    auto res =    stepworks::process::perform_process_controlled<int> (
                      stepworks::make_generator<int>(gen_plus_nine),

                  //    stepworks::wforward<int, std::forward_list> {  std::forward_list<int>()  },
    stepworks::wforward<int, std::vector> {  std::vector<int>()  },

                      control_less_then_100
                  );

//    int sz =res.second._dest.size();

    for ( const auto& k :   res.second._dest) {
      //  std::cout<<"\n..." << k;
        stepworks::ignore(k);
    };


    std::cout<<"\n*******************(generates <100)********************\n";


}



