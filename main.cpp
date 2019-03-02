#include <iostream>
#include <utility>
#include <string>
#include <variant>

#include <core/optional_type.hpp>
#include <typeinfo>

#include <core/ftypetraits.hpp>

using stepworks::types::var_tx;

using namespace std;

struct proc{};


struct f{};


struct s {
    int x=42;
    friend proc  operator >> (proc &&ip,  s &c);
    friend proc  operator << (proc &&op,  const s &c);
    int f1(const int& x){  return 42;}
};




template <typename Ta> 
struct strm{
    
};


proc  operator << (proc &&out, const s &c)
{
//out << c.x;
    return out;
}



proc  operator >> (proc &&in,  s &c)
{
 //   in >> c.x;
    return in;
}



int main ( int argc, char **argv )
{

    bool bt1= stepworks::has_member_f1t < s, int >();
    bool bf1= stepworks::has_member_f1t < s, std::string >();
    bool bf2= stepworks::has_member_f1t < strm<double>, std::string >();
    
    s c1,c2;

    proc p;
    
    std::move(p)>>c1>>c2;
    
    std::move(p)<<c1;
    //    cin >> c1;

//    cout << c1;

    return 0;
}
