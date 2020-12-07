//
// Created by karsten on 16.11.20.
//
#include "gtest/gtest.h"
#include <detect/detect_rec_writing.hpp>

#include <string>

struct writ_int_add{
    int _agg=0;
    void emplace_back(int x){ _agg+=x; }
    void emplace_front(int x){ _agg+=x; }
};

struct writ_int_set{
    int _agg=42;
    void insert(int x){ _agg=x; }
    auto operator[](unsigned int k)->int&{  _agg*=k;return _agg; }
};

struct writ_int_n{
    int _agg=0;
};


using stepworks::has_append;
using stepworks::has_append_front;
using stepworks::has_atref;
using stepworks::has_insert;

using stepworks::has_kvref;

TEST (dt_writing_test_case, detect_app) {
     auto  by= has_append<int,writ_int_add>::value;
     EXPECT_TRUE(by);
     auto  bn= has_append<std::string,writ_int_add>::value;
     EXPECT_FALSE(bn);
}


TEST (dt_writing_test_case, setect_at) {
    auto  by= has_atref<int,writ_int_set,unsigned int>::value;
    EXPECT_TRUE(by);
    auto  bn= has_atref<std::string ,writ_int_set,unsigned int>::value;
    EXPECT_FALSE(bn);
}


TEST (dt_writing_test_case, insert) {
    auto  by= has_insert<int,writ_int_set>::value;
    EXPECT_TRUE(by);
    auto  bn= has_insert<std::string ,writ_int_set>::value;
    EXPECT_FALSE(bn);
}

#include <map>

TEST (dt_writing_test_case, key_value) {
    auto  by= has_kvref<std::map<int,int>>::value;
    EXPECT_TRUE(by);
    auto  bn= has_kvref<int>::value;
    EXPECT_FALSE(bn);
}
