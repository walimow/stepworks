#pragma once

#include <array>
#include <core/optional_type.hpp>
#include <iostream>
#include <string.h>


using stepworks::types::var_t_info;

namespace stepworks::processtext{
    
    typedef enum{check_none, check_ls, check_le} check_len_option_t;
    
    template<typename R, unsigned int N=256>
    struct buffered{
        
        using fprocess_text_t=  var_t_info<R> (*)(const char*, int sz,  R&& );
        //fprocess_text_t _fproc;
        
        using fprepare_buffer_t= int (*)(char* );
        //fprepare_buffer_t _fprep;
        
        
        std::array<char, N> _buffer;
        
        var_t_info<R> process(fprepare_buffer_t fprep, fprocess_text_t fproc, std::ifstream& ifs , char delim = '\n'){
            //read-buffer
            ifs.getline(_buffer, N, delim );
            unsigned int len = strlen(_buffer);
            if (!ifs.fail() && fprep(_buffer)>0){
            //perform
                return fproc(_buffer, len);
            }
            else
                return off_info{-1};
        }
        
        /*
        var_t_info<R> process( fprocess_text_t fproc, std::ifstream ifs , char delim = '\n'){
            //read-buffer
            ifs.getline(_buffer, N, delim );
            if (!ifs.fail()){
                
                
            }
            
            //perform
        }*/
        
        
    };
    
    
    
}
