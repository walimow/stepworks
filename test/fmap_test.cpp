#include <steph/fmap.hpp>
#include <steph/fmapt.hpp>
#include <list>
#include <set>
#include <map>
#include <array>
#include "gtest/gtest.h"
#include <string>

using stepworks::steph::fm;

template <typename Ta>
struct trace_a_2{
      
    auto operator()(const Ta& a)const {
        auto k = 2*a;
        std::cout<<  k <<"\n";
        return k;
    }
};

using f = trace_a_2<int>;



TEST (fmapt_test_case, impl_atom){
     
     auto r = fm( f{} , 1);
     EXPECT_EQ( r,2);    
}


TEST (fmap_test_case, impl_list){
     
     auto l =std::list<int>{1,2,3,4,5,6};
     auto r = fm( f{} , l);
   //  EXPECT_EQ( r,2);    
}
//using stepworks::steph::fmx;

/*
TEST (fmap_test_case, impl_list_recogn){
    auto isl = stepworks::detect::is_iterable_pback < std::list<int> >::value;
    
   // auto tb = std::is_same_v< decltype(isl), std::true_type>();
    
    EXPECT_EQ( isl,true);    
    auto iskv = stepworks::detect::is_iterable_kv < std::list<int> >::value;
    EXPECT_EQ (iskv, false);
    auto isins = stepworks::detect::is_iterable_ins1 < std::list<int> >::value;
    EXPECT_EQ (isins, false);
}
*/

TEST (fmap_test_case, impl_set){
     
     auto l =std::set<int>{1,2,3,4,5,6};
     auto r = fm( f{} , l);
   //  EXPECT_EQ( r,2);    
}

/**/
TEST (fmapt_test_case, impl_set){
     
     auto l =std::set<int>{1,2,3,4,5,6};
     auto r = fm( f{} , l);
   //  EXPECT_EQ( r,2);    
}
/**/

TEST (fmap_test_case, impl_set_recogn){
    auto isl = stepworks::detect::is_iterable_pback < std::set<int> >::value_type();
    
   // auto tb = std::is_same_v< decltype(isl), std::true_type>();
    
    EXPECT_EQ( isl,false);    
    auto iskv = stepworks::detect::is_iterable_kv < std::set<int> >::value;
    EXPECT_EQ (iskv, false);
    auto isins = stepworks::detect::is_iterable_ins1 < std::set<int> >::value;
    EXPECT_EQ (isins, true);
}




TEST (fmap_test_case, impl_set_recogn2){
    
    auto isins = stepworks::detect::is_iterable_ins1 < std::set<int> >::value;
    EXPECT_EQ (isins, true);
}





TEST (fmap_test_case, impl_kv_recogn){
    auto isl = stepworks::detect::is_iterable_pback < std::map<std::string,int> >::value_type();
    
   // auto tb = std::is_same_v< decltype(isl), std::true_type>();
    
    EXPECT_EQ( isl,false);    
    auto iskv = stepworks::detect::is_iterable_kv < std::map<std::string,int> >::value;
    EXPECT_EQ (iskv, true   );
    auto isins = stepworks::detect::is_iterable_ins1 < std::map<std::string,int> >::value;
    EXPECT_EQ (isins, false);
}

/**/

TEST (fmap_test_case, impl_kv){
     
     auto l =std::map<std::string,int>{{"ogg",21},{"mil",9},{"dada",7}};
     auto r = fm( f{} , l);
   //  EXPECT_EQ( r,2);    
}

//using stepworks::steph::fmx;

TEST (fmapt_test_case, impl_kv){
     
     auto l =std::map<std::string,int>{{"ogg",201},{"mil",91},{"dada",71}};
     auto r = fm( f{} , l);
   //  EXPECT_EQ( r,2);    
}



TEST (fmap_test_case, impl_array){
    
    auto l =std::array<int,3>{133,233,333};
    auto r = fm( f{} , l);
    
}


TEST (fmapt_test_case, impl_array){
    
    auto l =std::array<int,3>{133,233,333};
    auto r = fm( f{} , l);
    
}

/**/


