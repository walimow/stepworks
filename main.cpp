
//using stepworks::types::var_tx;
#include <iostream>
#include <tuple>
#include <eal/util_t.hpp>
#include <eal/trace_t.hpp>
#include <eal/partl_t.hpp>
#include <eal/apply.hpp>
#include <eal/fo_t.hpp>



using namespace std;
using namespace stepworks::eal;




template < typename R, typename ...Args>
struct _fo_ {

    using F = R ( * ) ( Args... );
    F _f;


    auto operator() ( Args&&...args )
    {
        return _f ( args... );
    }
};

template < typename F>
struct _fox_ {

    F&& _f;

    template <typename ...Args>
    auto operator() ( Args&&...args ) const
    {
        return _f ( args... );

    }
};



//template <typename ...> struct f_fo;


struct f_fo {
    template < typename R,  typename ...Args>
    static auto f ( R ( *f ) ( Args... ) )
    {
        return  _fo_< R,Args...> {f} ;
    }
};



struct f_fox
//<R,Args...>
{
    template < typename F,  typename ...Args>
    static auto f ( F&& f )
    {
        return  _fox_< F> {std::move ( f ) } ;
    }
};

auto fa3 ( int a, int b, int c )
{
    return a+b+c;
}

int main()
{

    auto ts = std::make_tuple ( 1,2,3,4,5,6 );


    auto fox = f_fox::f ( [] ( int a, int b, int c )

    {
        return ( a+b ) *c;
    } );

    auto ret =  part_t<3>::lr_f ( std::move ( ts ),  std::move ( fox ) );


    std::cout<< "\nRet(>6?): "<<ret.first<<"\n";

    {

        auto fox = f_fo::f ( fa3 );

        auto ret =  part_t<3>::lr_f ( std::move ( ts ),  std::move ( fox ) );


        std::cout<< "\nRet(6?): "<<ret.first<<"\n";

    }
    {



        auto ret =  part_t<3>::lr_f ( std::move ( ts ),   f_fox::f (
                                          [] ( int a, int b, int c )

        {
            return ( a+b ) *c*b;
        }
                                      ) );


        std::cout<< "\nRet(>6?): "<<ret.first<<"\n";

    }

    {
        auto ret =  part_t<3>::lr_f ( std::move ( ts ),  stepworks::eal::fo::factor::gen ( fa3 ) );


        std::cout<< "\nRet(==>6?): "<<ret.first<<"\n";

    }

    
    ///eal
    {
        auto ret =  part_t<3>::lr_f ( std::move ( ts ),  stepworks::eal::fo::factor::gen ( fa3 ) );


        std::cout<< "\nRet(1+2+3?): "<<ret.first<<"\n";

    }
    
    {
        auto ret =  part_t<3>::lr_f ( std::move ( ts ),  stepworks::eal::fo::factor::gen ( [] ( int a, int b, int c )
        {
            return ( a+b ) *c*b;
        } ) );


        std::cout<< "\nRet(3*3*2?): "<<ret.first<<"\n";

    }

    return 0;

}

