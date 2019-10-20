#pragma  once

namespace  stepworks{

template <typename T>
constexpr auto is_framed( T&& a){
    return  false;
}

template <typename T, template<typename...>typename Frame>
constexpr auto is_framed( Frame<T>&& a){
    return   true; //is_framed_t<T>::check( std::move(a));
}

template <size_t N, typename ...>  struct arg_nth;

template <typename Ta, typename ...Rest>
struct arg_nth< 0, Ta, Rest...>{
    using type = Ta;
    auto get( const Ta& a, const Rest&...){
        return a;
    }
};

template <size_t N, typename Ta, typename ...Rest>
struct arg_nth< N, Ta, Rest...>{
    using type = typename arg_nth<N-1, Rest...>::type;
    auto get( const Ta& a, const Rest&...rest){
        return arg_nth<N-1, Rest...>(rest...);
    }
};


template <  typename ...Args>
struct  arg_n{

    template <size_t N>
    constexpr auto get(Args...args){
    return  arg_nth<N, Args...>::get(args...);
    }
        
    }; 



}
