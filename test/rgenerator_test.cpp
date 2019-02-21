#include "gtest/gtest.h"
#include <rw/rgenerator.hpp>
#include <process/proc.hpp>
#include <rw/wforward.hpp>
#include <list>

  //using Frr = Ta(*)(Ta&&);
  
  int gen_plus_nine(int&& x){
      return x+9;
}

   bool control_less_then_100(const int& x, void*){
       return x<100;
}


TEST ( generator_test, first )
{
    auto g = stepworks::make_generator<int>(gen_plus_nine);
    
    
    

  auto res =    stepworks::process::perform_process_controlled<int> (
        stepworks::make_generator<int>(gen_plus_nine),
        
        stepworks::wforward<int, std::list>{  std::list<int>()  },
        
        control_less_then_100
    );
    
    for ( const auto& k :   res.second._dest){
        std::cout<<"\n..." << k;
    };
    
    
    std::cout<<"\n*******************(generates <100)********************\n";    
    
    
}



