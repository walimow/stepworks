#include <rw/rstream.hpp>
#include <rw/wstream.hpp>


#include <util/offtype.hpp>
#include <util/optional_type.hpp>

#include <xtypes.hpp>

#include <iostream>
#include <map>
#include <string>
#include <list>
#include <cstdio>
#include <exception>

#include <boost/program_options.hpp>
#include <boost/filesystem.hpp>

#include "process_string_line.hpp"
#include "lines_to_set.hpp"
#include "index.hpp"
#include <rw/winsert.hpp>

#include <apply.hpp>



//#include <rw/wdictionary.hpp>


using stepworks::types::var_t_info;

namespace opt = boost::program_options;

using dict = stepworks::wtype::dict_index<string, unsigned int>;

//using dict = std::map<std::string, std::list<unsigned int>   >   ;


using test_t = stepworks::types::var_t<std::pair< std::string, unsigned int >>;

//using _a_ =stepworks::application::apply;
using stepworks::application::_;

void test_index()
{
    dict d;

    auto d1=
        _ (
            _ (
                _ (
                    _ ( std::move ( d ) ) ( test_t ( std::make_pair ( "hallo", 1 ) ) )
                )
                ( test_t ( std::make_pair ( "world", 2 ) ) )
            ) ( test_t ( std::make_pair ( "hallo", 3 ) ) )
        ) ( test_t ( std::make_pair ( "walim", 4 ) ) )
        ;







    int sz= d1.size();

    for ( const auto& kv: d1 ) {
        cout<< "\nkey:\t"<<kv.first<<"\t:";
        for ( const auto& e: kv.second )
            cout<< e<<"\t:";
    }

}


struct line_words {
    dict  _dict;
    const std::string _break_types=".,!?-";
    unsigned int _line=1;


    using  onword_t= void ( * ) ( std::string_view );
    onword_t _onword;
    //  std::list<std::string> _words;  //fft: optimize: just buffer_pos->dict

    //linewise   ///@todo: rest, nochars...
    auto operator () ( const char* ptr, unsigned int len )
    {

        bool is_onWord= ! ( isblank ( *ptr ) ||  _break_types.find ( *ptr ) != std::string::npos );
        unsigned int k=0;
        size_t switch_pos =k;

        for ( ; k<len; k++ ) {
            char c = * ( ptr+k );
            auto state = ! ( isblank ( c ) || _break_types.find ( c ) != std::string::npos );
            if ( is_onWord != state ) {
                if ( is_onWord ) { //a word ends
                    auto test=std::string_view ( ptr+switch_pos, k-switch_pos )  ;
                    _onword ( std::string_view ( ptr+switch_pos, k-switch_pos ) ) ;
                }
                switch_pos =k;
                is_onWord = state;
            }
        }
        if ( switch_pos < k && is_onWord ) //remain
            _onword ( std::string_view ( ptr+switch_pos, k-switch_pos ) ) ;

        return k;
    }

};

//using fprocess_text_t=  var_t_info<R> (*)(const char*, int sz,  R&& );

var_t_info<line_words> proces_dict ( const char*, int sz, line_words&& dpos )
{
    //todo impl....
    return std::move ( dpos );
}


int makelower ( char* pchar, unsigned int len )
{
    unsigned int k=0;
    for ( ; k<len; k++ ) {
        pchar[k]=tolower ( pchar[k] );
    }
    return k;
}



struct fabMakeIndex {

    dict _dict;

    auto f1 ( const  std::ifstream&r ) const
    {

        // stepworks::processtext::buffered<line_words>

        return _dict;
    }
};





int main ( int argc, char **argv )
{
    test_index();
    /*{
        const char* pcsz="...hallo, world, nice to be here...,yeah";
        line_words lw;
        lw._onword=[](std::string_view v) {
            std::cout<<"\nout: "<<v<<" ";
        };
        lw(pcsz, strlen(pcsz) );
    }*/
    opt::options_description desc ( "All options" );
    desc.add_options() ( "path", opt::value<std::string>(), "path" );

    ///@todo noparam
    std::string path="";
    std::string nowords_path="";
    std::set<std::string> _nowords;

    opt::variables_map vm;
    opt::store ( opt::parse_command_line ( argc, argv, desc ), vm );
    try {
        if
        ( auto haspath= vm.count ( "path" ) ;   haspath > 0 ) {
            if (
                path=  vm["path"].as<std::string>();
                path !="" ) {
                std::cout<<" path to file for make wordindex: "<< path;
            }
        } else {
            std::cout<<"\n\nno path to file for make wordindex";
        }
    } catch ( const std::exception& x ) {
        std::cout<<x.what();
    }

    try {
        if
        ( auto has_nowords_path= vm.count ( "nowords" ) ;   has_nowords_path > 0 ) {
            if (
                nowords_path=  vm["path"].as<std::string>();
                nowords_path !="" ) {
                lines_to_set l2s ( nowords_path );
                _nowords = std::move ( l2s._container );
            }
        }
    } catch ( const std::exception& x ) {
        std::cout<<x.what();
    }

    {
        // line_words{
        //apply_
        //
        auto r0= stepworks::make_rstream0 ( path ); //  is_valid<std::ifstream>(r0)  ){

        auto res =  stepworks::types::apply<  std::ifstream, dict> ( std::move ( r0 ), fabMakeIndex() );
        // );

    }




    return 0;
}
