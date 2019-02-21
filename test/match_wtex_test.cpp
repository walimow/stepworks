#include "gtest/gtest.h"
#include <matching/atom/wtex_atom_match.hpp>



///context senseless here, just for code...
namespace collatzfs_wtex {

    template <typename Ta>
        struct collatz_base{
            //    bool _break;
                Ta _test_start_value;
           
        };
        
        
	
        bool _break = false;
        
        
	bool is_odd(const   unsigned long & v, const collatz_base<unsigned long>*) { return (v % 2); }
	bool is_4(const   unsigned long & v, const collatz_base<unsigned long>*) { return (v ==4); }
	
	unsigned long feven(const unsigned  long&a, const collatz_base<unsigned long>*) { return a / 2; }
	unsigned long fodd(const unsigned  long&a,const  collatz_base<unsigned long>*) { return  3 * a + 1; }

	unsigned long on4(const unsigned long&v , const collatz_base<unsigned long>*ptr) {
            assert(ptr);
            _break=true;
            return v;
	}
}


TEST (match_wtex_test_case, collatz) {
{
        collatzfs_wtex::collatz_base<unsigned long> base;
    
	using W =  stepworks::matching::atom::wtex::_M<unsigned long, unsigned long, 
            collatzfs_wtex::collatz_base<unsigned long>
        >;
        
	using  namespace collatzfs_wtex;

	W::Op cv = 42;
	
	W::Op fv = stepworks::matching::atom::wtex::_ab<unsigned long, unsigned long
	   , collatzfs_wtex::collatz_base<unsigned long>
	>{ feven };

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

    std::cout << "WTEX...!\n"; 


	for (int i = 1; i < 100; i++)
	{
		unsigned int v = i;
		_break = false;
		std::cout << "\n\n";

		while (!_break) {
			std::cout << v << '\t';
			v = collatz(v, &base);

		}
	}
}
}

