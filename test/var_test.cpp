#include "gtest/gtest.h"

#include <core/optional_type.hpp>
#include <core/optional.hpp>
#include <util/ignore.hpp>


TEST(  var_test, off_var_type){
    
    stepworks::types::var_t_type<int> v42{42};
    
    auto x = stepworks::types::_asserted<int>( v42);
    stepworks::ignore(x);
}
