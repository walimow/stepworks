
#include "gtest/gtest.h"
#include <rw/rforward.hpp>
#include <rw/select.hpp>
#include <rw/rstream.hpp>

#include <util/optional.hpp>

#include  <list>
#include <sstream>

using namespace stepworks;

TEST(rtype_test,  rlist) {
    
    auto  l123 = make_forward_readeable<int, std::list>(  std::list<int>{21,42,63});
    EXPECT_EQ(l123._src.size(),3);
    
     auto sa= _go_(std::move(l123));
    
    EXPECT_EQ(  stepworks::types::_optional(   sa.first,-1),21);
    
    auto r2 = _go_( std::move(sa.second));
    
    EXPECT_EQ(  stepworks::types::_optional(   r2.first,-1),42);
}



TEST(rtype_test,  rstream_isstream) {
    
    auto  l123 =   make_rstream
    <int, std::istringstream>
    (   std::istringstream {"21 42 63"} );
    
    auto sa= _go_(std::move(l123));
    
    EXPECT_EQ(  stepworks::types::_optional(   sa.first,-1),21);
    
    auto r2 = _go_( std::move(sa.second));
    
    EXPECT_EQ(  stepworks::types::_optional(   r2.first,-1),42);
}


////using prime
#include <prim/rcontainer.hpp>
////TODO Test r-prime
