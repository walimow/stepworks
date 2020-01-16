#include <rw/itx.hpp>
#include "gtest/gtest.h"
#include <iostream>
#include <vector>
#include <forward_list>
#include <deque>
#include <rw/wforward.hpp>
#include <core/optional.hpp>


TEST (itread_test_case, impl_ull_ch) {

    using c3=char[3];

    {
        stepworks::itx< unsigned long long>  rulch;

        std::cout << "\n*******************************************\n"<<rulch.size_factor<<"\n"<<rulch.has_rest<<"\n"<<rulch.size_effectiv<<"\n************************************\n";
    }

    {
        stepworks::itx< unsigned long long,c3>  rulch;

        std::cout << "\n*******************************************\n"<<rulch.size_factor<<"\n"<<rulch.has_rest<<"\n"<<rulch.size_effectiv<<"\n************************************\n";
    }
}



TEST (itread_test_case, impl_ull_ch_fail) {

    unsigned long long ulltest= 0x00ab10fafe120000;

    auto res_w =
        stepworks::itx< unsigned long long>::write_corpus_forward_ret<std::list>(
            // std::move( vv)
            std::list<unsigned char> {}
            //  std::vector<unsigned char>{}
            , ulltest
        );
        
        {
          auto res_w =
        stepworks::itx< unsigned long long>::write_corpus_forward_ret<std::list>(
            // std::move( vv)
            std::list<unsigned char> {}
            //  std::vector<unsigned char>{}
            , ulltest
        );  
            
        }
        

    std::cout <<  std::hex<<ulltest<< "\n++++++++++++++++++++++++++++++++++++++++++++\n";
    int x =0;
    {
        std::cout << std::hex;
        for ( const  auto& a:  res_w /*._dest*/) {
            x++;
            std::cout << (int)a<<"\t";
        }
        std::cout << "\n"<<x<< "\n++++++++++++++++++++++++++++++++++++++++++++\n";
    }
    std::cout<<"\n...\n";
    {

        auto rr= stepworks::itx< unsigned long long>::read_corpus_v(
                     std::move(
                         res_w 
                     )
                 );

        auto xret = !rr.first.index() ? std::get<0>(rr.first) : 0; // stepworks::types::_optional( rr.first, 0);

        std::cout <<"nR: "<< std::hex<<xret<<"\n";

    }




}
