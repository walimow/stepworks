
#include "gtest/gtest.h"
#include <box/box.hpp>


//#include <util/boxm.hpp>
#include <map>
#include <list>
#include <detect/detect_box.hpp>


using stepworks::bxx::box;



TEST( box_test_case, detect_f){
    auto f = stepworks::detect::is_box<int>::value;
    EXPECT_FALSE(f);
}

TEST( box_test_case, detect_t){
    auto bx0 = box<int, std::vector>({1}) ;

    auto t = stepworks::detect::is_box<decltype(bx0) >::value;
    EXPECT_TRUE(t );
}

