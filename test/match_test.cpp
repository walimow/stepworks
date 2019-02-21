#include "gtest/gtest.h"
//#include <matching/matching_atom.hpp>
#include <matching/match_atom.hpp>
#include <foab.hpp>

//using stepworks::matching::atomar::match;
//using  stepworks::matching::atomar::make_match;

using stepworks::matching::atomar::_M;

using stepworks::foab;

//collatz

namespace collatz_matching{

bool is_even(const int&a){  return !(a%2);}

auto fodd (const  int&a){ return 3*a+1; };

auto feven ( const unsigned int& a){ return a/2; };

}

//ulimate : odd
//match<foab<int,int>>  modd{collatz_matching::fodd};


//_M <unsigned int,unsigned int>modd00{ collatz_matching::fodd };



using namespace collatz_matching;

//_M<int,int,int> 
//auto mcomplete_collatz =_M<unsigned int,unsigned int, unsigned int>(is_even, feven, fodd);

//


//mcollatz( collatz_matching::is_even,collatz_matching::feven,                                  collatz_matching::fodd);



