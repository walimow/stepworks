#pragma once

namespace stepworks{
    
    template <typename Ty>
    struct true_value{
      Ty _val;  
    };
  
    template <typename Ty>
    auto make_true_value(Ty a){
        return true_value<Ty>{std::forward<Ty>(a)};    
    }
    
    template <typename Ty>
    struct fail_value{
      Ty _val;  
    };
    
    template <typename Ty>
    auto make_fail_value(Ty a){
        return fail_value<Ty>{std::forward<Ty>(a)};    
    }
    
    
    template <typename Ty>
    constexpr bool is_indicate_fail( const Ty& ){ return false;}
    
    template <typename Ty>
    constexpr bool is_indicate_fail( const fail_value<Ty>& ){ return true;}
    
    
    
    template <typename Ta, typename S, template<typename, typename> typename  FTrue , template<typename> typename FFail, typename FType>
    struct when_true{
        FTrue<Ta, S> && _ftrue;
        
        constexpr  auto operator()(Ta&& a, S&& s ){
            return _ftrue(std::move(a), std::move(s));
        }
        
        constexpr  auto operator()(fail_value<FType>&& a, S&& s , FFail<FType>&& ff){
            auto r= std::move(ff)(a._val);
            return make_pair( r, std::move(s) );
        }
        
        constexpr  auto operator()(fail_value<FType>&& a, S&& s ){
            return std::move(s) ;
        }
    };
    
    /*
    template <typename Ta, typename S, template<typename...> FTrue >
    constexpr auto when_indicate_true(  Ta&& l, S&& r ){
        
    }
    
    template <typename Ta, typename S, template<typename...>typename F >
    //constexpr auto when_indicate_fail(  fail_value<Ta>&& l, S&& r, F ){
        
    }
    */
}
