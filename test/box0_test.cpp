//
// Created by karsten on 25.11.20.
//


#include "gtest/gtest.h"
#include <box/box.hpp>
#include <box/util.hpp>
#include <vector>

using stepworks::bxx::box;

using  stepworks::bxx::box_type;

TEST (boxtest, test0)
{

   using T= int;
   using BOX = box<T, std::vector>;
   using BOX_T = box_type<T, std::vector>;

   BOX b0;

    EXPECT_EQ( BOX_T::typex(b0._value), 1  );
   EXPECT_EQ( BOX_T::type_sz(b0._value), 0 ) ;  //default type: empty container

    {
        BOX b0(BOX::eatom);

        EXPECT_EQ( BOX_T::typex(b0._value), 0  );
        EXPECT_EQ( BOX_T::type_sz(b0._value), -1 ) ;  //default type: empty container

    }


    BOX b00 ( BOX::eaggregate );

    EXPECT_EQ( BOX_T::typex(b00._value), 1  );
    EXPECT_EQ( BOX_T::type_sz(b00._value), 0 );


    BOX b0b ( std::vector<BOX>{} );

    EXPECT_EQ( BOX_T::typex(b0b._value), 1  );
    EXPECT_EQ( BOX_T::type_sz(b0b._value), 0 );



    BOX ba0;


    EXPECT_EQ( BOX_T::type_sz( ba0._value ), 0 );

    {
        BOX b0(1);
        EXPECT_EQ( BOX_T::typex(b0._value), 0  );
        EXPECT_EQ( BOX_T::type_sz(b0._value), -1 ) ;  //default type: empty container
    }
    {

        BOX b0{1};

        EXPECT_EQ( BOX_T::typex(b0._value), 1  );   //now aggregator with one element
        EXPECT_EQ( BOX_T::type_sz(b0._value), 1 ) ;  //sz
    }
    {
        BOX b0{1,2};
        EXPECT_EQ( BOX_T::typex(b0._value), 1 );
        EXPECT_EQ( BOX_T::type_sz(b0._value), 2 ) ;  //default type: empty container
    }
   BOX b3{ 1,2,{3}};
   BOX b4({ 1, BOX({2,3,4})});
    {
        BOX b0({1, BOX({2, 3, 4}), 7});
        EXPECT_EQ( BOX_T::typex(b0._value), 1 );
        EXPECT_EQ( BOX_T::type_sz(b0._value), 3 );
        EXPECT_EQ( BOX_T::count_total(b0._value), 5 );
    }

}
