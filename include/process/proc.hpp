#pragma once

#include <util/optional_type.hpp>

namespace stepworks::process{

    
    
    // ******   returns <R,W>
    
    //breaks on a0
    template< typename Reader, typename Ta, template<typename>typename Form= stepworks::types::var_t>
    struct proc{        
        Reader&& _r;        
        template < typename Writer  /*= decltype(Reader::atype)*/ >
        auto operator ()(Writer&&w)->std::pair<Reader,Writer >{
             
            if (std::pair<  Form<Ta>, Reader> a0r =   stepworks:: _go_<Ta>(  std::move( _r  ) )  ; (a0r.first)  ){
                  return  {
                   
                      proc{ std::move(a0r.second)  } 
                        (   stepworks::_go_ 
                        //<Ta, Writer,Form>
                        (  std::move(w),   a0r.first ))
                  };
                  //if ()
            }
            else{
                 return std::make_pair(std::move(a0r.second), std::move(w));
            }
        }
        
        template < typename Writer  /*= decltype(Reader::atype)*/ >
        auto go(Writer&&w){
             
            if (std::pair<  Form<Ta>, Reader> a0r =   _go_(_r)  ; (a0r.first)  ){
                  return proc{ std::move(a0r.second)  } (    _go_(w, a0r.first) );
            }
            else{
                 return std::make_pair(std::move(a0r.second), std::move(w));
            }
        }
        
    };
    
    template <typename Ta, typename Foab >
    struct _T{
        //using F= Tb(*)(const Ta&);
        const Foab& _foab;
        auto operator()(const Ta&a){
            return _foab(a);
        }
    };
    
///with transfer
  template< typename Reader, typename Ta,typename Foab, template<typename>typename Form= stepworks::types::var_t>
    struct proct{
        
        Reader&& _r;
        Foab && _tfoab;
        

        template < typename Writer  /*= decltype(Reader::atype)*/ >
        auto operator ()(Writer&&w)->std::pair<Reader,Writer >{
             
            if (std::pair<  Form<Ta>, Reader> a0r =   stepworks:: _go_<Ta>(  std::move( _r  ) )  ; (a0r.first)  ){
                const Ta& v =   _asserted( a0r.first);
                  return   {
                   
                      proct{ std::move(a0r.second) , std::move( _tfoab) } 
                        (   stepworks::_go_ 
                            (  std::move(w), _tfoab( v ))
                        )
                  };
            }
            else{
                 return std::make_pair(std::move(a0r.second), std::move(w));
            }
        }
        
        template < typename Writer  /*= decltype(Reader::atype)*/ >
        auto go(Writer&&w){
             
            if (std::pair<  Form<Ta>, Reader> a0r =   _go_(_r)  ; (a0r.first)  ){
                  return proc{ std::move(a0r.second)  } (    _go_(w, a0r.first) );
            }
            else{
                 return std::make_pair(std::move(a0r.second), std::move(w));
            }
        }
        
    };    
    
    
    template<
    typename Ta,
    typename Reader,
     
    //template<typename...>
    typename Writer , template<typename>typename Form= stepworks::types::var_t>
    auto perform_process( Reader&& r, Writer   && w){      
        return proc<Reader,Ta,Form>{ std::move(r) }(std::move(w));
    }
    
    template<
    typename Ta,
    typename Foab,
    typename Reader,
    
        typename Writer , template<typename>typename Form= stepworks::types::var_t>
    auto perform_process( Reader&& r, Writer   && w, Foab&& foab){      
        {
        auto test = proct<Reader,Ta,Foab,Form>{ std::move(r),std::move(foab) };
        }
        return proct<Reader,Ta,Foab,Form>{ std::move(r),std::move(foab) }
        (std::move(w) );
    }
    
        
    //skips on a0, breaks on r0
    template< typename Reader>
    struct proc0{
        
        Reader&& _r;
        
        //breaks on a0
        template < typename Writer, typename Ta, template<typename>typename FormA, template<typename>typename FormR>
        auto operator ()(Writer&&w){
             
            if (std::pair<  FormA<Ta>, FormR<Reader>> a0r0 =   _go_(_r) ; (a0r0.first)  ){
                if (a0r0.second)
                    return proc0{ std::move(a0r0.second)  } (    _go_(w,a0r0.first) );
                else{
                   return  make_pair(a0r0.second,  _go_(w,a0r0.first)) ;
                }
            }
            else{                
                if (a0r0.second)   ///skip
                    return proc0{ std::move(a0r0.second)  } (  w );
                else{   ///break
                    return  make_pair(a0r0.second,  std::move(w)) ;
                }
                //return std::make_pair(std::move(a0r.second), std::move(_r));
            }
        }
    };
        
    ///break on handle   ///@todo implement h
    template< typename Reader,   
        template <typename> typename  HandledOffR, typename HandlerInstance >
    struct proc0h{
        
        Reader&& _r;
        
        HandlerInstance   _handler;
        
        //
        template < typename Writer, typename Ta, template<typename>typename FormA, template<typename>typename FormR>
        auto operator ()(Writer&&w){
             
            if (std::pair<  FormA<Ta>, FormR<Reader>> a0r0 =   _go_(_r) ; (a0r0.first)  ){
                if (a0r0.second)
                    return proc0h{ std::move(a0r0.second)  } (    _go_(w,a0r0.first) );
                else{
                   return  make_pair(a0r0.second,  _go_(w,a0r0.first)) ;
                }
            }
            else{                
                if (a0r0.second)   ///skip
                    return proc0h{ std::move(a0r0.second)  } (  w );
                else{   ///break
                    if (auto rreset0  = _handler(  std::get<0>(  std::move(a0r0.second)  )   ); (!rreset0))   //handler says no
                            return  make_pair(a0r0.second,  std::move(w)) ;
                    else
                          return proc0h{ std::move( std::get<1> (rreset0)) } (  w );
                            
                }
                //return std::make_pair(std::move(a0r.second), std::move(_r));
            }
        }
         
        
    };
    
  
    
}


