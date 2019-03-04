#include <rw/rstream.hpp>
#include <rw/wstream.hpp>

#include <core/valid.hpp>
#include <core/offtype.hpp>
#include <core/optional_type.hpp>

#include <rw/index.hpp>
#include <rw/rstream.hpp>

//#include <xtypes.hpp>

#include <iostream>
#include <map>
#include <string>
#include <list>
#include <cstdio>
#include <exception>

#include <boost/program_options.hpp>
#include <boost/filesystem.hpp>

#include  <util/lines_to_set.hpp>

#include <apply/apply_writer.hpp>

#include "wordindex.h"

using stepworks::types::var_t_info;

namespace opt = boost::program_options;



using test_t = stepworks::types::var_t<std::pair< std::string, unsigned int >>;

using stepworks::application::apply;
using stepworks::application::_;


int main ( int argc, char **argv )
{

    opt::options_description desc ( "All options" );
    desc.add_options() ( "path", opt::value<std::string>(), "path" );
    desc.add_options() ( "nowords", opt::value<std::string>(), "nowords" );

    ///@todo noparam
    std::string path="";
    std::string nowords_path="";
    std::set<std::string> _nowords;

    wdict dict;

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
                nowords_path=  vm["nowords"].as<std::string>();
                nowords_path !="" ) {
                lines_to_set l2s ( nowords_path );
                _nowords = std::move ( l2s._container );
            }
        }
    } catch ( const std::exception& x ) {
        std::cout<<x.what();
    }

    if (path.size())
    {
        auto r0= stepworks::make_rstream0 ( path ); //  is_valid<std::ifstream>(r0)  ){
        if (
            stepworks::types::_valid_(r0))
        {

            using TN =  var_type<   decltype(r0) >::_Type;
            auto  rr=    _asserted<TN>  ( std::move(r0));
            
            wordindex::file2lines< TN> wx{ dict};
            auto result =  stepworks::application::_ ( std::move(wx) ) ( std::move(rr) );

            int sz =wordindex::trace_dict(result);                
            std::cout<<   "\nsz: "<< sz<<"\n";
        }
    }
    
    return 0;
}
