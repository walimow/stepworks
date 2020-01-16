#pragma once

#include <deque>

namespace stepworks {

//just design...
    
///support for listmatch
/// (srcReader)
/// reads into a vector
//  buffer+srcReader may be work together as reader 
//  morphology: dynamic, runtime

    ///INCOMPLETE!!!
    
    /*
     template <typename Ta,
          typename Stream = std::istream,
          template <typename > typename Form = var_t>
     */
     template <typename Ta,
     typename RServer,
     typename RBuffer=std::deque<Ta>,
      template <typename > typename Form = var_t>
      struct ror_buffered{
          RBuffer _buffer;
          typename RBuffer::iterator _buffer_iterator;
          RServer&& _server;
          std::size_t buffer_sz() { return buffer.size();}
          auto prepare (unsigned int sz){   //completeness
              for (unsigned int k =_buffer.size(); k< sz; k++ ){
                  auto [a0, R] =  _go_(_server);
                  if (!a0)
                      return buffer_sz() -sz;
                   else{
                     _buffer.push_back( _asserted(a0));  
                } 
            }
            return  buffer_sz();   
          }
    };
    
    template <typename Ta,     typename RServer,     typename RBuffer,template <typename > typename Form>
    auto _go_(ror_buffered<Ta, RServer, RBuffer>&&g)->std::pair< Ta,ror_buffered<Form<Ta>, RServer, RBuffer>>{
        ///@todo ... ?
    }
     
    
    


}
