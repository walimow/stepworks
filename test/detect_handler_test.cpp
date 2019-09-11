#include "gtest/gtest.h"

#include <core/ftypetraits.hpp>
#include <core/optional_type.hpp>

using stepworks::types::var_t;

struct A0{
  auto  operator ()(){ return 1;}
};

struct H1{
  void handle_off ( int  )//-> stepworks::types::var_t<int>
  {
       // return //stepworks::types::  var_t<int>(42);
       // 42;
    }
};




TEST ( detectx, test_0 )
{
    auto hasnot =  stepworks:: has_off_handler<A0,int>().value;
    EXPECT_EQ(hasnot, false);
}


TEST ( detectx, test_1)
{
    auto has =  stepworks:: has_off_handler<H1,int>().value;
    EXPECT_EQ(has, true);
}
