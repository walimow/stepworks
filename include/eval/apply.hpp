#pragma once

#include <utility>
#include "evaluate.hpp"

#include <functional>

using stepworks::evaluation::eval_auto;

namespace stepworks::evaluation {
///std::apply with evaluation

	namespace detail {
		template <class F, class Tuple, std::size_t... I>
		constexpr decltype(auto) apply_impl(F&& f, Tuple&& t, std::index_sequence<I...>)
		{
			return  std:: invoke(std::forward<F>(f),  	
				eval_auto::get	(
			  	std::get<I>(std::forward<Tuple>(t)	)
				)
				...
			)
				;
		}
	}  // namespace detail

	template <class F, class Tuple>
	constexpr decltype(auto) apply (F&& f, Tuple&& t)
	{
		return detail::apply_impl(
                        std::forward<F>(f), 
			std::forward<Tuple>(t),
			std::make_index_sequence<std::tuple_size_v<std::remove_reference_t<Tuple>>>{});
	}


}
