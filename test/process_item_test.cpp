#include "gtest/gtest.h"
#include <process/process_item.hpp>
#include <util/ignore.hpp>
#include <foab.hpp>

using  stepworks::process::process_item;



TEST(processitem_test,  ident_impl) {
 
    // 1
    process_item< 
        decltype(  stepworks::make_foab<int,int>( stepworks::ident<int> ) )
    > 
        item_ident(stepworks::make_foab<int,int>( stepworks::ident<int>));
    
    // 2    
    auto it_ident= stepworks::process::make_item(stepworks::make_foab<int,int>( stepworks::ident<int>));
    stepworks::ignore(it_ident);
    
}
