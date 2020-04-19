//
// Created by kh on 19.04.20.
//
#include "gtest/gtest.h"
#include <util/strutil.hpp>
#include <string>

using stepworks::util::ltrim_view;
using stepworks::util::rtrim_view;
using stepworks::util::trim_view;

TEST(  strutil_test, sview1l) {
    std::string sL="           l2r";
    std::cout<< "VIEW LTrim\n>>"<< ltrim_view(sL)<<'<';
}


TEST(  strutil_test, sview1r) {
    std::string sL="   *  r2lL       ";
    std::cout<< "VIEW RTrim\n>>"<< rtrim_view(sL)<<'<';
}



TEST(  strutil_test, sview1lr) {
    std::string sL="   *  r2l *       ";
    std::cout<< "VIEW RTrim\n>>"<< trim_view(sL)<<'<';
}