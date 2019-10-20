#include "gtest/gtest.h"
#include <stw.type_traits.hpp>
#include <iostream>
#include <string>
    
#include <util/stw.types.hpp>


template <typename X> 
struct anyx{
	X*x;
	static void f() {}
};



/*
struct int_sub {	
	auto operator ()(int&& r)->std::pair<int, int> {
		return std::make_pair(  std::move(r)-1,1) ;
	}
	using _R_ = int;
	using _T_ = int;
};
*/

struct int_ab{
	auto operator ()(int r)->int {
		return r;
	}
	
	auto apply(int r)->int {
		return r;
	}

	using Res = int;
	using Arg = int;
};


struct int_ab_read {
	int _state;
	auto operator ()()->std::pair<int_ab_read, int> {
		return  std::make_pair(int_ab_read{ std::move(*this)._state - 1 } , 1);
	}

	
	using Res = int;
	using Arg = int;
};


struct int_ab_read_corr {
	int _state;
	
	auto operator ()(int_ab_read_corr&& e)->std::pair<int_ab_read_corr, int> {
		return  std::make_pair(int_ab_read_corr{ std::move(e)._state - 1 }, 1);
	}


	using Arg = int_ab_read_corr&&;

	using Res = decltype(std::declval<int_ab_read_corr>()( std::declval<Arg>() ));
		
};


using stepworks::test_ab_morph;




TEST(morphology_test_case,  process_transform_0) {
	
	auto v0 = test_ab_morph < int>::value;
        EXPECT_EQ(v0,0);
	
	//std::cout <<  << '\n';
	auto v1 = test_ab_morph < int_ab, int,int   >::value;
        EXPECT_EQ(v1,1);
	
	v1 =  stepworks::autoform::test_ab_morph < int_ab   >::value ;
	EXPECT_EQ(v1,1);


	v0=stepworks::autoform::test_ab_morph < int_ab_read   >::value ;
        EXPECT_EQ(v0, 0);

	v1 =  stepworks::autoform::test_ab_morph < int_ab_read_corr   >::value ;
        EXPECT_EQ(v1,1);

	v1 =  test_ab_morph < int_ab_read_corr, int_ab_read_corr&&, std::pair<int_ab_read_corr  ,   int> >::value;
        EXPECT_EQ(v1,1);

}

/////reader/////
#include <stwtype_traits.hpp>

using namespace stw;

struct r_yes {
    using element_type=int;
};

//std::pair<geht, int> 
constexpr auto  _(r_yes&&) {
    return 
     std::make_pair( std::move(r_yes{}),  (int)42);
  //   42;
}

struct none_off_all {
};


TEST(morphology_test_case2,  reader1) {
 
    EXPECT_EQ(    is_reader_tR< r_yes>::value, false);
}

    
    
    
    

