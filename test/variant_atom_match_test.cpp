#include "gtest/gtest.h"
#include <matching/atom/variant_atom_match.hpp>
#include <matching/atom/carray_atom.match.hpp>



namespace va_collatz_matching{

bool is_even(const unsigned int&a){  return !(a%2);}
bool is_odd(const unsigned int&a){  return (a%2);}

auto fodd (const  unsigned  int&a){ return 3*a+1; };

auto feven ( const unsigned int& a){ return a/2; };

bool is_4(const unsigned int&a){  return a==4;}

auto f4 (const  unsigned  int&a)->unsigned int{ return 4; };

}

using namespace stepworks::matching::atom::var;
using namespace va_collatz_matching;

auto of0 = final<unsigned int, unsigned int>{fodd};


//auto m0 =  (M<unsigned int, unsigned int>){(final<unsigned int, unsigned int>){ fodd }};
