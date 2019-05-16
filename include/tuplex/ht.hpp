#include <tuple>
#include <utility>


namespace stepworks::tuplex{
    
    template < typename T , typename... Ts >
    auto head( std::tuple<T,Ts...> t )
    {
    return  std::get<0>(t);
    }
    
    
    template < std::size_t... Ns , typename... Ts >
    auto tail_impl( std::index_sequence<Ns...> , std::tuple<Ts...> t )
    {
    return  std::make_tuple( std::get<Ns+1u>(t)... );
    }

    template < typename... Ts >
    auto tail( std::tuple<Ts...> t )
    {
    return  tail_impl( std::make_index_sequence<sizeof...(Ts) - 1u>() , t );
    }


    template <typename Ta, typename ...Args>
    auto ht( std::tuple< Ta, Args... >&& src ){
        return make_pair( head( std::move(src) ) , tail( std::move(src) ) );
                    
    }
    
    
}
