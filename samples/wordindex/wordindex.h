#pragma once

#include <iostream>
#include <map>
#include <string>
#include <list>
#include <cstdio>
#include <exception>

#include <boost/program_options.hpp>
#include <boost/filesystem.hpp>


using wdict = stepworks::wtype::dict_index<string, unsigned int>;

using stepworks::util::trim;

namespace wordindex {


template<  typename OnWords>
struct line_words {
  
    OnWords&  _on_word;
    
    const std::string _break_types=".,!?-;'`:()\"";   ///todo option   //`All :	1527,
    const unsigned int min_sz=3;
    
    auto operator () (unsigned int line , const char* ptr, unsigned int len ) const
    {
        bool is_onWord= ! ( isblank ( *ptr ) ||  _break_types.find ( *ptr ) != std::string::npos );
        unsigned int k=0;
        size_t switch_pos =k;
        for ( ; k<len; k++ )
            
        for ( ; k<len; k++ ) {
            char c = * ( ptr+k );
            auto state = ! ( isblank ( c ) || _break_types.find ( c ) != std::string::npos );
            if ( is_onWord != state ) {
                if ( is_onWord && k-switch_pos>=min_sz ) { //a word ends
                    //auto test=std::string_view ( ptr+switch_pos, k-switch_pos )  ;
                   const  auto& str= string(ptr+switch_pos, k-switch_pos);
                    _on_word (  line,   str ) ;    ///todo
                    //_on_word (  line,  (const  std::string&)(   std::string_view  ( ptr+switch_pos, k-switch_pos))) ) ;    ///todo
                }
                switch_pos =k;
                is_onWord = state;
            }
        }
        if ( switch_pos < k && is_onWord  && k-switch_pos>=min_sz){ //remain
            const auto& str= string(ptr+switch_pos, k-switch_pos);
//            _on_word (  line, std::string(  std::string_view ( ptr+switch_pos, k-switch_pos ) )) ;   //?
            _on_word (  line, str.c_str()) ;   //strage behaviour on the last word
        }
        return k;
    }
};




const size_t N=120 ;
char s[N];

template<typename F = std::ifstream>
struct file2lines {
    //template <typename S>
    //using void fapply(const S&); 
    wdict&  dict;
   
    struct _on_word_{
        wdict& _dict;
        void  operator() (unsigned int line,  const std::string& s) {
         //   string test=s;trim(test);
            stepworks::primary::_f_ (   _dict  , make_pair(s,line));
        }    
    };
    
    _on_word_ _on_word{dict};
    line_words<_on_word_> _flines{ _on_word };   ///todo foab   
    
    auto f1 (  F&& ist, unsigned int line=1) const->  wdict& {
        //read lines
        //char s[N];
        
        int test = dict.size();
       
        ist.getline(s,N-1);  //??
        int len = strlen(s);
        std::string_view value(s); //!!
        
        if (!ist.fail()){
            std::cout<<line<<"\t"<< value<<"\n";
            if (value=="."){
                std::cout<<"\n==pt==\t";
            }
            for (auto &c: s)
                c=tolower(c);
                
            _flines(line,(const char*) &s, len);
            //(unsigned int line , const char* ptr, unsigned int len )
          //   _on_word(line, value);
            return file2lines{ dict }.f1(std::move(ist), ++line);        
        }
        return   dict ;
    }
    auto f0()const {
        return *this;
    };
    
    //(unsigned int line , const char* ptr, unsigned int len )
};

int trace_dict(const wdict&d){
    int rc=0;
    for (const auto& kv: d  ){
        rc++;
        cout<< "\n>"<<kv.first<<"<:\t";
        for (const auto& e : kv.second)
            cout<< e<<',';
    }    
    return rc;
}

}


