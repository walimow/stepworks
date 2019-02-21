#pragma once

#include <util/argtype.hpp>
#include <cassert>
#include <utility>

/// FunctionObject A -> B

namespace stepworks{
    
    template <typename ...>  struct foab;
    
    template <typename Ta, typename Tb>
    struct  foab<Ta,Tb>{

        using F = Tb(*)(const  Ta&);      //&&
        using _argument_type=Ta;
        using _return_type=Tb;
        const F _f;
        foab(F f):_f(f){
            assert(_f);
        }
        auto operator ()( Ta&& a) const->Tb{
            return _f( std::forward<_argument_type> (a)  );
        }        
        /*
        auto operator ()( const Ta& a) ->Tb{
            return _f( std::forward<_argument_type> (a)  );
        }        
        */
        auto f1( Ta&& a)const ->Tb{
            return _f( std::forward<_argument_type> (a)  );
        } 
    };
    
    template <typename Base>
    struct foab<Base>{
    public:        
        const Base& _base;
        using Ta =  
        //arg_1_t<typename Base::_f>
            decltype (typename Base::_argument_type());
     
        //template<typename Ta>        
        auto operator ()( const Ta& a)const ->decltype ( _base(  a) )const {
            return _base(a);
        }            
        };
    
        
    template <typename Ta>
    auto ident( const Ta& a)-> Ta{  return a;}   // return  std::forward<Ta>(a);}
    
    template<typename Ta, typename Tb>
    auto make_foab( typename  foab<Ta,Tb>::F f)->foab<Ta,Tb>{
        return foab< Ta, Tb >{f};
    }
    

    
     template<typename Base>  //typename Ta, typename Tb
    auto make_foab( const Base& f){
        return  foab < Base >{f};
    }
    
    
    template <typename _Foab_base, typename Ta>
    auto apply_foab(const _Foab_base& base, Ta a)->decltype ( base(a)){
        return   foab<decltype(base) >{base}(a);
    }
     
    
      
    

     
    
}
