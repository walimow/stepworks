#pragma once

#include  <type_traits>


namespace stepworks::evaluation{
    
    
template <typename Ta>
using f0_t=    decltype(::std::declval<Ta>() ());

/// if experimental/type_taits is not available

namespace detail {
	template <class Default, class AlwaysVoid,
		template<class...> class Op, class... Args>
	struct detector {
		using value_t = std::false_type;
		using type = Default;
	};

	template <class Default, template<class...> class Op, class... Args>
	struct detector<Default, std::void_t<Op<Args...>>, Op, Args...> {
		// Note that std::void_t is a C++17 feature
		using value_t = std::true_type;
		using type = Op<Args...>;
	};

} // nam

struct nonesuch {};

template <template<class...> class Op, class... Args>
using is_detected = typename detail::detector<nonesuch, void, Op, Args...>::value_t;

template <template<class...> class Op, class... Args>
using detected_t = typename detail::detector<nonesuch, void, Op, Args...>::type;

template <class Default, template<class...> class Op, class... Args>
using detected_or = detail::detector<Default, void, Op, Args...>;

/// ...till here


template <typename R>
struct eval {
	//static constexpr  R test( R&& r){ return std::move(r);}
	template<class Q>
	typename std::enable_if <std::is_same<Q, R>::value, R>::type
		static constexpr get(const Q& r)
	{
		return r;
	}

	template<class T>
	typename std::enable_if <is_detected<  f0_t, T >::value
		, R
	>::type
		static constexpr get(const T& r)
	{
		return r();
	}


	template<class Q>
	typename std::enable_if <std::is_same<Q, R>::value, R>::type
		static  constexpr get_t(Q&& r)
	{
		return r;
	}

	template<class T>
	typename std::enable_if <
		is_detected<  f0_t, T >::value
		&&
		std::is_same<  decltype(std::declval<T>()()), R >::value
		, R
	>::type
		static  constexpr get_t(const T& r)
	{
		return r();
	}

};



struct eval_auto {
	template<class T>
	typename std::enable_if <is_detected<  f0_t, T >::value
		, f0_t<T> >  ::type
		static constexpr get(T&& r)
	{
		return r();
	}


	template<class T>
	typename std::enable_if < !is_detected<  f0_t, T >::value
		, T>::type
		static constexpr get(T&& r)
	{
		return r;
	}
};



    
} 
