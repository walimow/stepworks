//
// Created by kh on 14.01.21.
//

#include <detect/detect_cmorph.hpp>
#include <cmorph/imorph/apply.hpp>
#include <cmorph/imorph/process.hpp>
#include <gtest/gtest.h>
#include <vector>
#include <iostream>
#include <cmorph/imorph/boxtrans.hpp>

namespace {

    template <typename Ty, typename Tb=Ty>
    struct neg{
        auto operator()(const Ty& a)const->Tb{
            return  -a;
        }
    };


    template <typename Ty, typename Tb=Ty>
    struct neghalf{
        auto operator()(const Ty& a)const->Tb{
            return  -a/3;
        }
    };

}

TEST (cmorph_test, imorphii){

    std::vector<int> v={1,2,3,6,7,42};

    auto rv = stepworks::imorph::apply(v, neghalf<int, double >{});

    std::cout<< std::dec <<"'\nF?:: ";
    std::cout<< typeid(rv).name()<<'\n';
    for (const auto &a : rv){
        std::cout<<'\t'<<a ;
    }

}

TEST (cmorph_test, imorphiL){

    std::vector<int> v={1,2,3,6,7,42, 99};

    auto rv = stepworks::imorph::apply(v, [](auto a){ return -a;});

    std::cout<< std::dec <<"'\nF?:: ";
    std::cout<< typeid(rv).name()<<'\n';
    for (const auto &a : rv){
        std::cout<<'\t'<<a ;
    }
}

    template <typename Ty>
    struct wp_max{
        Ty _value=0;
        bool used=false;
        auto operator()(const Ty& a)const {
            return  used? _value> a? _value : a : a;
        }

        static auto apply(wp_max<Ty>&& m_, const Ty& a)->wp_max<Ty>{
            auto m = std::move(m_);
            m._value=a;
            m.used=true;
            return m;
        }
    };


TEST (cmorph_test, imorph_proc_max){
    std::vector<int> v={1,2,3,167,6,7,42, 99};
    auto x = stepworks::imorph::process_imorph(v, wp_max<int>{});
    EXPECT_EQ(x._value,167);
}

