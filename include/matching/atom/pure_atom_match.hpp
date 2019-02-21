#pragma once

///@todo static/ compiletime 

namespace stepworks::matching::atom::pure {
    
 
	template< typename...>	struct M;

	template< typename R , typename A>
	struct M<R,A>
	{
		using F = R(*)(const A&);
		F _f;
		
		using construct_arg = F;

		M<R, A>(construct_arg f) : _f(f) {}
		
		auto operator()(const A&a) const {
			return _f(a);
		}
	};

	template< typename R, typename A>
	auto   _M( typename  M<R, A>::construct_arg args) {
		return M<R, A>{args};
	 }


	template< typename R, typename A, typename ...Rest>
	struct M<R, A, Rest...> : public M<R, Rest...>
	{
		using Q = bool(*)(const A&);
		Q _q;
		using F = R(*)(const A&);
		F _f;

		using construct_arg = std::pair< 
			std::pair<Q,F>, 
			typename M<R,  Rest...>::construct_arg
		>;

		M<R, A, Rest...>( M<R,A, Rest...>::construct_arg a ) 
			:_q(a.first.first),   _f(a.first.second),
			M<R, Rest...>(a.second)
		{}

		constexpr const M<R, Rest...>& next()const { return (const M<R, Rest...>&) *this; }
		auto operator()(const A&a) const {
			return  _q(a) ?    _f(a) : next()(a);
		}
	};

	template< typename R, typename A, typename ...Rest>
	auto   _M(typename  M<R, A, Rest... >::construct_arg args) {
		return M<R, A, Rest...>{args};
	}



    
    
}
