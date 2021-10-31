//
// Created by kh on 06.06.21.
//

#include <gtest/gtest.h>
#include <detect/detect_variant.hpp>
#include <variant>
#include <string>

using  stepworks::detect::is_variant_v;

TEST( detectrw, test_int){
    EXPECT_FALSE(  is_variant_v<int> );
}


TEST( detectrw, test_string){
    EXPECT_FALSE(  is_variant_v<std::string> );
}


TEST( detectrw, test_var){
    using vt= std::variant<int,std::string>;
    EXPECT_TRUE(  is_variant_v<vt> );
}