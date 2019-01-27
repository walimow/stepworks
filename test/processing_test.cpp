
#include "gtest/gtest.h"
#include <rw/rforward.hpp>
#include <rw/rforwardt.hpp>
#include <rw/wstream.hpp>
#include <process/proc.hpp>


#include <iostream>
#include <sstream>
#include <forward_list>
#include <list>

TEST ( processing_test, rempty )
{

    bool test=false;
    auto src = stepworks::make_forward_readeable ( std::forward_list<int> {} );
    {        
        test = src._it ==src._src.end();
        EXPECT_EQ ( test, true );

        auto res = stepworks::make_forward_readeable ( std::move ( src._src ), std::move ( src._it ) ) ;
        test = res._it ==res._src.end();
        EXPECT_EQ ( test, true );        
    }

}


TEST ( processing_test,  rw_1 )
{
    std::cout<<"\n*******************1********************\n";
    auto res =    stepworks::process::perform_process<int> ( stepworks::make_forward_readeable ( std::forward_list<int> {1} ),
                  stepworks::wstream<int, std::ostream> {  std::move (std::cout ),"..."   } );
    std::cout<<"\n*******************2********************\n";
}


TEST ( processing_test,  rw_123 )
{
    std::cout<<"\n*******************1..********************\n";
    auto res =    stepworks::process::perform_process<int> (
        stepworks::make_forward_readeable ( std::forward_list<int> {1,2,3,42} ),
                  stepworks::wstream<int, std::ostream> { std::move ( std::cout ), "\t"  } );
    std::cout<<"\n*******************..42********************\n";
}

TEST ( processing_test,  rw_t_impl )
{
 stepworks::make_forward_readeable_t ( std::list<int> {1,2,3,42} );
}


namespace proctest{
    
    struct textform{
        
      std::string operator ()( const int& v  ){
          std::ostringstream ost;
          ost<< "-(" << v <<")-";
          return ost.str();
    }
      
    };
    
}

TEST ( processing_test,  rw_123_t )
{
    auto form = proctest ::textform();
 
    
    std::cout<<"\n****************>>>1..********************\n";
    auto res =    stepworks::process::perform_process<int> (
                    
                    stepworks::make_forward_readeable_t ( std::list<int> {1,2,3,42} ),                  
                    stepworks::wstream<std::string, std::ostream> { std::move ( std::cout ), "\t"  } ,
                    std::move(form)
                                                            
                                                           );
 
    std::cout<<"\n*******************..42<<<********************\n"; 
}

