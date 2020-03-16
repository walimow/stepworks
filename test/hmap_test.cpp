#include "gtest/gtest.h"
#include <util/hmapx.hpp>


TEST (hmap_test, hmapx)
{
    using SMap = stepworks::hmapx<std::string, std::string, int>;
    
    SMap root{"*root*"};
    SMap child{"*child*",&root};
    
}


