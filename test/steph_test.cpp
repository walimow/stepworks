
#include "gtest/gtest.h"
#include  <steph/functor.hpp>
#include <list>


template <typename Ty>
struct nof{

//   using return_type =int;
//   using arg_type =Ty;
   
   int  any(Ty){ return 42;} 
};



template <typename Ty>
struct valf{
   using ret_type = Ty;
   using arg_type =const Ty&;
   auto operator ()( const Ty& x){ return x;} 

  static  auto fx(
       const Ty& x
   ) { return 4;} 

};


using stepworks::steph::is_function_object;
using stepworks::steph::is_function_object_t;

TEST (steph_test, fo_false)
{
    auto bf = is_function_object< nof<int>() >().value;
    EXPECT_EQ(bf, false);
}


TEST (steph_test, fo_true)
{
    auto bt = is_function_object< valf<int> >::value;
    EXPECT_EQ(bt, true);
}

TEST (steph_test, fo_true2)
{
    auto bt = is_function_object_t< valf<int> >::value;
    EXPECT_EQ(bt, true);
}

////functor

//using stepworks::steph::is_functor;


//fo 
template<typename Ta>
struct f2{
    
    auto operator()(const Ta& a)const{
        return 2*a;
    }
    using ret_type =Ta;
    using arg_type =Ta;
};

///fmap, list
template<typename Ta, template <typename >typename F>
auto fmap(std::list<Ta>&& li, const F<Ta>& f) {
    std::list<typename F<Ta>::ret_type> lo;
    for(const auto a: std::move(li))
        lo.push_back(f(a));
    return lo;    
};



TEST (steph_test, fo_fmaplist1){
   
    
    auto lo= fmap(std::list{1,2,3}, f2<int>{} );    
    int sum=0;
    for (const auto a:lo){
        sum+=a;
    }
    EXPECT_EQ(sum,12);
    
}




