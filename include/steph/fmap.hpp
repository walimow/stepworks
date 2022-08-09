#pragma once
#include <type_traits>
#include  <util/detect.hpp>


namespace stepworks::steph
{

//pure
template < typename Ft,  typename Ta         >
auto fmap(const Ft & f, const Ta&  a) {
    return   f ( a );    // std::invoke<Ft,  int > (  f ,   a   );
}

/*
template < typename Ft,  typename FTa, 
typename std::enable_if<
    std::is_invocable < decltype< (FTa)>::value,  >, 
*/

template < typename Ft,  typename Ta, typename K,template<typename...> typename Container>
typename std::enable_if<
    stepworks::detect::is_iterable_kv <Container<K,Ta>>::value, 

Container< K, decltype( std::declval<Ft>() ( std::declval<Ta>() ) )    > > ::type
fmap(const Ft & f,  const Container< K,Ta>& c) {
    using Tb = decltype(f( std::declval<Ta>() ));
    Container<K,Tb> res;
    for (const auto& [k,a]: c)
        res.insert( std::make_pair (  k, fmap( f,a) ) );
    return res;
}



template < typename Ft,  typename Ta, template<typename...> typename Container>
typename std::enable_if<
    stepworks::detect::is_iterable_pback < Container<Ta> >::value,  
Container< decltype( std::declval<Ft>() ( std::declval<Ta>())) > > ::type
fmap(const Ft & f,  const Container<Ta>& c) {
    using Tb = decltype(f( std::declval<Ta>() ));
    Container<Tb> res;
    for (const auto& a: c)
        res.push_back( fmap( f,a)   );
    return res;
}

template < typename Ft,  typename Ta, template<typename...> typename Container>
typename std::enable_if<
    stepworks::detect::is_iterable_ins1 <Container<Ta>>::value,   
Container< decltype( std::declval<Ft>() ( std::declval<Ta>() )) >  >::type
fmap(const Ft & f,  const Container<Ta>& c) {
    using Tb = decltype(f( std::declval<Ta>() ));
    Container<Tb> res;
    for (const auto& a: c)
        res.insert(
           fmap( f ,  a   )
        );
    return res;
}

///pure array
//template < typename Ft,  typename Ta, template<typename...> typename Container>
template < typename Ft,  typename Ta,  std::size_t Sz>
auto
fmap(const Ft & f,  const std::array<Ta,Sz>& c) {
    using Tb = decltype(f( std::declval<Ta>() ));
    std::array<Tb,Sz> res;
    for ( std::size_t k=0; k < c.size(); k++)
        res[k]=   fmap( f , c[k]  );
    return res;
}




}
