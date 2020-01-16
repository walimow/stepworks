#include "gtest/gtest.h"
#include <rw/stx.hpp>
#include <rw/itx.hpp>

using stepworks::mk_itxcorpus;
using stepworks::itx_write;

TEST (stx_test_case, mkcorpus) {
    char c6[6]="hall?";
     auto r123 = mk_itxcorpus(1, 42.0 );
     auto rs = itx_write(r123);   
     
    std::cout <<  std::hex<< "\n++++++++++++++++++++++++++++++++++++++++++++\n";
    int x =0;
    {
        std::cout << std::hex;
        for ( const  auto& a:  rs /*._dest*/) {
            x++;
            std::cout << (int)a<<"\t";
        }
        std::cout << "\n"<<x<< "\n++++++++++++++++++++++++++++++++++++++++++++\n";
    }
    std::cout<<"\n..śtx\n";
     
}
