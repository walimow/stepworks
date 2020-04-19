
#pragma once
#include <map>
#include <unordered_map>
#include <util/iox.hpp>

using stepworks::iox::to_type_textable;

namespace stepworks{
    //super as const
    template <class K, class T, 
    class  Compare= std::less<K>,  
    class Allocator = std::allocator<std::pair<const K, T> > >
    struct hmap{
        using Map=std::map<K,T,Compare, Allocator> ;
        const hmap * _psuper=nullptr;
        Map  _map;
        
        std::pair< typename Map::const_iterator, int > select (const K&k, int level=0)const {
            auto it = _map.find(k);
            return  it != _map.end() ?
                 std::make_pair(it, level)
                 :
                 _psuper ? _psuper->select(k, level+1) : std::make_pair(it, -1);
        }


        template <typename  Output_T=std::ostream>
        Output_T&  write(Output_T& out,
                const std::string kon="k: ", const std::string koff=": ",
                const std::string von=" <", const std::string voff="> ",
                const std::string start=" <", const std::string end="> ",
                const std::string delim=" "
                )const{
            out << start<<delim;
            for(const auto& [k,v]: _map)
                out               <<kon<< to_type_textable(k) <<koff<<delim                <<von<< to_type_textable(v)    <<voff<<delim            ;
            if (_psuper)
                _psuper->write( out, kon,koff,von, voff,start, end, delim);
            out << end<<delim;
        return out;
}


    };



    
}
