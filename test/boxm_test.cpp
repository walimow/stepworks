#include "gtest/gtest.h"
#include <string>
#include <box/boxm.hpp>
#include <exception>
#include <map>



using stepworks::bxm::boxm;

TEST (boxm_test_case, impl_m)
{
 //   std::vector< boxm<std::string, std::string, std::map> > vgehtdas;
}


using stepworks::bxm::to_string;


using stepworks::bxm::mk_box;


using stepworks::bxm::mk_box_value;



TEST (boxm_test_case, impl_initializer_list)
{

    try {
        std::cout << "mk_box(Ty a ) ==1\n";
        auto res1 = mk_box<std::string, std::string, std::map>({{"kk", "jl"}});

    }
    catch (const std::exception& x) {
        std::cout<<"x--here1x<< \n"<<x.what()<<"\n";
    }

    std::cout<<"mk_box(Ty a ) ==2\n";
    {
    //    auto x = mk_box<std::string, std::string, std::map>({"aaaa","hkjhkhkh"} );
    }
    std::cout<<"xxxx-here1x<< \n"<<"\n";
}


TEST (boxm_test_case, impl_initializer_list2)
{

    boxm<std::string, std::string, std::map> bxm0({{"aaaa","hkjhkhkh"}, {"aaab","hkhkh"} });
//      auto x = mk_box<std::string, std::string, std::map>( {{"aaaa","hkjhkhkh"}, {"aaab","hkhkh"} } );

}



TEST (boxm_test_case, impl_initializer_list1)
{
    std::cout<<"\nTRY===============\n";

             boxm<std::string, std::string, std::map> bxm0({{"aaaa","hkjhkhkh"}, {"aaab","hkhkh"} });


    std::cout<< "\nBOX(r) to_string([==2==]): "<< to_string(bxm0,"[ ","]\n"," : ");
    std::cout<<"\n===============\n";
}



/*

TEST (boxm_test_case, impl_initializer_list2)
{
    auto res1 = mk_box<unsigned long , std::vector>(1);
    {
        using _B=stepworks::bx::box<unsigned long, std::vector>;

        _B x = mk_box<unsigned long , std::vector> ({ 1, _B{2,3},4 } );
    }
}

TEST (boxm_test_case, impl_initializer_list_per_value)
{
    auto m2 = box<unsigned long int, std::vector>{  mk_box_value<unsigned long int, std::vector>( {1,
                                                                                                   mk_box<unsigned long int, std::vector>({2,3})
                                                                                                          ,4} )};
    std::cout<< "\nBOX(per impl_initializer_list_per_value) to_string: "<< to_string(m2,"[ ","]\n"," : ");
}

using stepworks::bx::l2r::move_box;

TEST (boxm_test_case, move_box)
{
    std::cout<< "\n===============================================================================================\n";
    auto bx0 = mk_box<int, std::vector>( {1} );
    std::cout<< "\nBOX(r) to_string: "<< to_string(bx0);

    auto bx2 = move_box< int, std::vector,std::vector>( std::move( bx0 ));
    std::cout<< "\nBOX(rmoved) to_string: "<< to_string(bx2);

}
 */