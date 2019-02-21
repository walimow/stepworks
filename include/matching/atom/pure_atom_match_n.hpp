#pragma once

namespace pure_match_n {

	template< typename R, typename A,  int N>
	struct M;

	template< typename R, typename A>
	struct M<R, A, 0>
	{
		using F = R(*)(const A&);
		F _f;

		using construct_arg = F;

		M<R, A,0>(construct_arg f) : _f(f) {}

		auto operator()(const A&a) const {
			return _f(a);
		}
	};

	template< typename R, typename A, int N>
	struct M : M<R,A,N-1>
	{
		using Q = bool(*)(const A&);
		Q _q;
		using F = R(*)(const A&);
		F _f;

		using construct_arg = std::pair<
			std::pair<Q, F>,
			typename M<R, A,N-1>::construct_arg
		>;

		M<R, A, N>(M<R, A, N>::construct_arg a)
			: _q(a.first.first), _f(a.first.second),
			M<R, A,N-1>(a.second)
		{}

		
		constexpr const M<R, A, N-1>& next()const { return (const M<R, A,N-1>&) *this; }
		auto operator()(const A&a) const {
			return  _q(a) ? _f(a) : next()(a);
		}

	};


	template <typename...> struct rdeep;

	template <typename R, typename A> 
	struct rdeep<R,A>  {
	
		///just default
		constexpr unsigned int RD(R(*)(const A&)) { return 0; }
		///case:default
		constexpr unsigned int RD( 
			std::pair <
				std::pair<
				bool (*)(const A&),
				R(*)(const A&)>
			, R(*)(const A&)
			>) {
			return 1;
		}
	};
	

	template <typename R, typename A, typename ...Rest>
	struct rdeep<R, A, Rest...>  {

		constexpr unsigned int RD(
			const 
			std::pair <
			std::pair<
			bool(*)(const A&),
			R(*)(const A&)>
			, R(*)(const A&)
			>& x) {
			return 1 + rdeep<R, Rest...>::RD(x.second);
		}
	};

	//constexpr unsigned int r_deep()

	
	template< typename R, typename A>
	auto _M(
		std::pair<bool(*)(const A&), 
			R(*)(const A&)> qfs[], 
		  R(*default_final)(const A&)) 
	{
	
	}
	
}
