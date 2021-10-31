#include "gtest/gtest.h"
//#include <stwtype_traits.hpp>

#include <detect/detect_rw.hpp>
#include <variant>
#include <optional>

TEST (rwmorph_test_case, read0)
{
    //int x;
}



struct r_yes {
    using element_type=int;
};


struct r_yes0 {
    using element_type=int;
    //using element_type=int;
};



//std::pair<geht, int> 


struct r_yesc {
    using element_type=int;
    using context_type=int;
};

struct w_yes {
    using element_type=int;
   };


struct w_yesc {
    using element_type=int;
    using context_type=int;

    
};


constexpr auto  _(r_yes&&r) {
    return 
     std::make_pair( std::move(r),  (int)42);
//     42;
}


constexpr auto  _(r_yes&&r, const int&) {
    return 
     std::make_pair<>( std::move(r),  (int)42);
//     42;
}

constexpr w_yes  _(w_yes&&r, int&&) {
    return  std::move(r); //w_yes{};     
}

///yust a  compiler confusing test
constexpr w_yes  _(w_yes&&r, int&&, const int&) {
    return w_yes{};     
}

constexpr w_yesc  _(w_yesc&&r, int&&, const int&) {
    return w_yesc{};     
}

constexpr auto  _(r_yesc&&r, const int&) {
    return 
     std::make_pair( std::move(r),  (int)42);
//     42;
}


struct none_off_all {
};



TEST(rwmorph_test_case,  reader01y) {
 
    using stepworks::r0::is_reader_tR;
    
    bool b = is_reader_tR< r_yes >::value;
    EXPECT_EQ( b , true);
}

TEST(rwmorph_test_case,  reader01n) {
 
    using stepworks::r0::is_reader_tR;
    
    bool b = is_reader_tR< none_off_all >::value;
    EXPECT_EQ( b , false);
}


TEST(rwmorph_test_case,  readerc1y) {
 
    using stepworks::rcx::is_reader_tR;
    
    bool b = is_reader_tR< r_yesc >::value;
    EXPECT_EQ( b , true);
}


TEST(rwmorph_test_case,  writer01y) {
 
    using stepworks::w0::is_writer_tR;
    
    bool b = is_writer_tR< w_yes >::value;
    EXPECT_EQ( b , true);
}


TEST(rwmorph_test_case,  writer01n) {
 
    using stepworks::w0::is_writer_tR;
    
    bool b = is_writer_tR< w_yesc >::value;
    EXPECT_EQ( b , false);
}


TEST(rwmorph_test_case,  writer01cy) {
 
    using stepworks::wcx::is_writer_tR;
    
    bool b = is_writer_tR< w_yesc >::value;
    EXPECT_EQ( b , true);
}



TEST(rwmorph_test_case,  writer01cn) {
 
    using stepworks::wcx::is_writer_tR;
    
    bool b = is_writer_tR< w_yes >::value;
    EXPECT_EQ( b , false);
}


template <typename Ty = int>
struct r_off {
    Ty _yvalue;
};

template <typename Ty>

constexpr auto mk_off(Ty&& v) {
    return r_off < Ty >{std::move(v)};
}

struct okv {
    using element_type= std::optional<int>;
    using base_return_framed_type
        = std::variant < r_off<okv>, std::optional<int>>;        
    using context_type= int;    
};

 

constexpr auto _(okv&& r) {
    return
        std::make_pair
        <okv::base_return_framed_type, okv::element_type >
    (
            mk_off( okv{ std::move(r) })
            ,
            std::optional<int>{ (int)42 }
    );
}

constexpr okv::base_return_framed_type  _(okv&& w, std::optional<int>&&) {
    return        
            mk_off( okv{ std::move(w) });
}



struct okvc {

    using element_type= std::optional<int>;
    using base_return_framed_type  = std::variant < r_off<okvc>, std::optional<int>>;
    using context_type = int;
};

constexpr okvc::base_return_framed_type  _ (okvc&& w, std::optional<int>&&, const int&) {
    return        
            mk_off( okvc{ std::move(w) });
}


constexpr auto _(okvc&& r, const int& ) {
    return
        std::make_pair
     < okvc::base_return_framed_type,   okvc::element_type >
    (
          mk_off( okvc{})     ,    std::optional<int>{ (int)42 }
    );
}

TEST(rwmorph_test_case,  readerxy) {
    using stepworks::r0x::is_reader_tR;    
    bool b = is_reader_tR< okv >::value;
    EXPECT_EQ( b , true);
} 


TEST(rwmorph_test_case,  readercxy) {
    using stepworks::rxcx::is_reader_tR;    
    bool b = is_reader_tR< okvc >::value;
    EXPECT_EQ( b , true);
}

TEST(rwmorph_test_case,  writerxy) {
    
    using  stepworks::wx0 ::is_writer_tR;
    bool b = is_writer_tR< okv >::value;    
    EXPECT_EQ( b , true);    
}

TEST(rwmorph_test_case,  writerxyc) {
    
    using  stepworks::wxcx ::is_writer_tR;
    bool b = is_writer_tR< okvc >::value;    
    EXPECT_EQ( b , true);    
}
