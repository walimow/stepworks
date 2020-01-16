#pragma once

#include <utility>

namespace stepworks::util{

template <std::size_t N, std::size_t K>
struct npow
{
       static const unsigned long long value = N * npow<N, K - 1>::value;
};

template <std::size_t N>
struct npow<N, 0>
{
       static const int value = 1;
};

}
