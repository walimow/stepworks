
#include "gtest/gtest.h"
#include <util/box.hpp>

using stepworks::bx::box;

TEST (box_test_case, impl_1)
{
 std::vector<box<int, std::vector> > vgehtdas;
}

using stepworks::bx::to_string;


using stepworks::bx::mk_box;


using stepworks::bx::mk_box_value;


TEST (box_test_case, impl_initializer_list)
{
    auto res1 = mk_box<int, std::vector>(1);
    {
    auto x = mk_box<unsigned long int, std::vector>({1,2,3} );
    }
}


TEST (box_test_case, impl_initializer_list1)
{
    auto m2 = mk_box<unsigned long int, std::vector>( {1,
        mk_box<unsigned long int, std::vector>({2,3})
        ,4} );
    std::cout<< "\nBOX(r) to_string: "<< to_string(m2,"[ ","]\n"," : ");
}


TEST (box_test_case, impl_initializer_list2)
{
    auto res1 = mk_box<unsigned long , std::vector>(1);
    {
        using _B=stepworks::bx::box<unsigned long, std::vector>;
        
    _B x = mk_box<unsigned long , std::vector> ({ 1, _B{2,3},4 } );
    }
}

TEST (box_test_case, impl_initializer_list_per_value)
{
    auto m2 = box<unsigned long int, std::vector>{  mk_box_value<unsigned long int, std::vector>( {1,
        mk_box<unsigned long int, std::vector>({2,3})
        ,4} )};
    std::cout<< "\nBOX(per impl_initializer_list_per_value) to_string: "<< to_string(m2,"[ ","]\n"," : ");
}

using stepworks::bx::l2r::move_box;

TEST (box_test_case, move_box)
{
    std::cout<< "\n===============================================================================================\n";
    auto bx0 = mk_box<int, std::vector>( {1} );
    std::cout<< "\nBOX(r) to_string: "<< to_string(bx0);
    
    auto bx2 = move_box< int, std::vector,std::vector>( std::move( bx0 ));
    std::cout<< "\nBOX(rmoved) to_string: "<< to_string(bx2);
    
}

/*

using stepworks::mk_box;

TEST (box_test_case, impl_initializer_list2)
{
    auto x = mk_box<int, std::initializer_list >(1, {2, 3}, 4);
}

*/
