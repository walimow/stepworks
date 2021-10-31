#include <tuple>

namespace stepworks::eal{

    template <typename Ta, typename...DestTupleTypes>
    constexpr auto cons(  std::tuple<DestTupleTypes...>&& t,  Ta&& a){  return
        std::tuple_cat(t, std::tuple<Ta>( a ));
    } 
      
      
      template < typename...DestTupleTypes  , typename...Src 
      >
      constexpr auto cons(  std::tuple<DestTupleTypes...>&& t,  std::tuple<Src...>&& a){
          return
        std::tuple_cat(t,  a );
    } 
    
    
   
}
