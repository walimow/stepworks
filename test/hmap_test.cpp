#include "gtest/gtest.h"
#include <util/hmapx.hpp>
#include <util/hmap.hpp>

TEST (hmap_test, hmapout)
{
    using HMap = stepworks::hmap< std::string, int>;
    HMap hm;
    hm.write(std::cout);
}


TEST (hmap_test, hmapx)
{
    using SMap = stepworks::hmapx<std::string, std::string, int>;
    
    SMap root{"*root*"};
    SMap child{"*child*",&root};


    child.write(std::cout);
    
}


