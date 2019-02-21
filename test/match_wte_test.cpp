#include "gtest/gtest.h"
#include <matching/atom/wte_atom_match.hpp>




namespace collatzfs {

	static bool _break = false;

	bool is_odd(const   unsigned long & v) { return (v % 2); }
	bool is_4(const   unsigned long & v) { return (v ==4); }
	
	unsigned long feven(const unsigned  long&a) { return a / 2; }
	unsigned long fodd(const unsigned  long&a) { return  3 * a + 1; }

	unsigned long on4(const unsigned long&v) {
		_break = true;
		return v;
	}
}


TEST (match_wte_test_case, collatz) {
{
	using W =  stepworks::matching::atom::wte::_M<unsigned long, unsigned long>;
	using  namespace collatzfs;

	W::Op cv = 42;
	
	W::Op fv = stepworks::matching::atom::wte::_ab<unsigned long, unsigned long>{ feven };

//	W::Op w = (W*) nullptr;

	{
		auto  quatsch = W{ is_odd, 42, 11 };
	
	}

	//auto Q = new  W{ is_4, on4,  feven };

	auto collatz = 
		W{ is_odd,
		fodd,
		new  W {is_4, on4,  feven}
		//	feven

	};

	{
		auto  quatsch = W( is_odd,
		new   W	(is_4, on4,  feven)
		, 11 );

	}

    std::cout << "Hello World!\n"; 


	for (int i = 1; i < 100; i++)
	{
		unsigned int v = i;
		_break = false;
		std::cout << "\n\n";

		while (!_break) {
			std::cout << v << '\t';
			v = collatz(v);

		}
	}
}
}
