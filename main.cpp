
#include <rw/rforward.hpp>
#include <rw/rforwardt.hpp>
#include <rw/wstream.hpp>
#include <process/proc.hpp>


#include <iostream>
#include <list>
#include <vector>
#include <forward_list>

void test1() {
    bool b=false;
    bool b1=false;
    {

        auto li = stepworks::make_forward_readeable(std::list<int> {});
        b = li._it ==li._src.end();


    }
    {

        auto li = stepworks::make_forward_readeable(std::list<int> {1});
        b = li._it ==li._src.end();

        auto ll =  stepworks::_go_( std::move(li) );
        auto* pli1 = & ll.second;
        //const auto& li1 =  stepworks::_go_( std::move(li) ).second;
        b = pli1->_it ==pli1->_src.end();
        b1 = li._it ==li._src.end();
/*
        void* p0 =&pli1->_it;
        void* p1 =&li._it;
        void* p2 =&pli1->_src;
        void* p3 =&li._src;
        std::cout<<"";
        */
        /**/
        ////
        /*
         auto internal_peek() -> typename decltype(data)::iterator
                       //  ^^^^^ here
        {
        if (m_activeStackSize) // peek from stack
        {
        typename decltype(data)::iterator itr = data.end();
        // ^^^^^ and here

         */


    }
    {
        auto li = stepworks::make_forward_readeable(std::list<int> {1,2,42});

//   stepworks::process::proc { stepworks::make_forward_readeable(std::list<int>{1,2,42})  }( stepworks::wtype::wstream<int,std::ostream>{ std::move(  std::cout)  } );

        auto  fwl = stepworks::make_forward_readeable(  std::list<int> {1,2,42});
        /*
          auto res =    stepworks::process::perform_process<int>( stepworks::make_forward_readeable(  std::list<int>{1,2,42}),
                                                            stepworks::wstream<int, std::ostream>{ std::move( std::cout)   } );
        */
    }
}

using stepworks::make_forward_readeable;

void test() {
    bool test=false;
    {
    auto src = stepworks::make_forward_readeable(std::list<int> {});
    {
        test = src._it ==src._src.end();
        std::cout<< "\n before: "<<  std::boolalpha <<test;

        auto res = make_forward_readeable(std::move(src._src), std::move( src._it)) ;
        test = res._it ==res._src.end();
        std::cout<< "\n result: "<<  test;
        std::cout<< "\n b2r: "<< ( res._it ==src._src.end());
        std::cout<< "\n r2b: "<< ( src._it ==res._src.end())<<"\n";
    }
    }
}

void test_rt() {
    bool test=false;
    {
    auto&& src = stepworks::make_forward_readeable_t(std::list<int> {});
     {
        test = (bool)src; //src._it == std::move(src._src).end();
        std::cout<< "\n before: "<<  std::boolalpha <<test;

        auto&& res = stepworks::make_forward_readeable_t(std::move(src._src), std::move( src._it)) ;
        test = res;  // _it ==res._src.end();
        std::cout<< "\n result: "<<  test;
     }
    }
    {
    auto&& src = stepworks::make_forward_readeable_t(std::list<int> {1,2,3});
     {
        test = (bool)src; //src._it == std::move(src._src).end();
        std::cout<< "\n before: "<<  std::boolalpha <<test;

        auto&& res = stepworks::make_forward_readeable_t(std::move(src._src), std::move( src._it)) ;
        test = res;  // _it ==res._src.end();
        std::cout<< "\n result: "<<  test;
     }
    }
}

int main ( int argc, char **argv )
{
    test_rt();
    return 0;
}
