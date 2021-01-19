//
// Created by kh on 07.12.20.
//

#include <vector>

#include <gtest/gtest.h>
#include <detect/detect_tostring.hpp>

using stepworks::bxx::detect::supports_tostring;

TEST(detect_tostring, pos){
    auto y = supports_tostring<int>::value;
    EXPECT_TRUE(y);
}


TEST(detect_tostring, neg){
    auto n = supports_tostring<std::vector<int>>::value;
    EXPECT_FALSE( n);
}




