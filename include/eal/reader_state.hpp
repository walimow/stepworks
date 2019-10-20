#pragma once


namespace stepworks::eal {
 
       template <typename...>    struct rstate;
    
       
    ///definitiv reader: generator etc   
    template <typename Reader, typename Ta>
    struct rstate<Reader, Ta>{
        Reader&& _reader;
        auto operator()(){
          auto [ r1 , a]  = std::move(_reader);  
       //   _reader= std::move(r1);
          return a;
        } 
    };
    
}
