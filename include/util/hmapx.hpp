
#pragma once
#include <map>
#include <unordered_map>
#include <ostream>
#include <util/iox.hpp>

using stepworks::iox::to_type_textable;

namespace stepworks{
    //super as const
    //contains an additional particle (as 'cargo')
    template <class Cargo,class K, class T,
    class  Compare= std::less<K>,
    class Allocator = std::allocator<std::pair<const K, T> >
            ,template <typename ...> typename map_t= std::map
            >
    struct hmapx{
        Cargo _cargo;   
        using Map=map_t<K,T,Compare, Allocator> ;
        const hmapx * _psuper=nullptr;
        Map  _map;
        inline auto  avail0(const K& k)const {  return _map.find(k) == _map.end() ; }
        std::pair< typename Map::const_iterator, int > select (const K&k, int level=0) const {
            auto it = _map.find(k);
            return it != _map.end() ? 
                 std::make_pair(it, level)
                 :
                 _psuper ? _psuper->select(k, level+1) : std::make_pair(it, -1);
        }

        template <typename  Output_T=std::ostream>
        Output_T&  write(Output_T& out,
                         const hmapx * plimit= nullptr,
                         const std::string cargo_on="c:< ", const std::string cargo_off=">:c ",
                         const std::string kon="k: ", const std::string koff=": ",
                         const std::string von=" <", const std::string voff="> ",
                         const std::string start=" <", const std::string end="> ",
                         const std::string delim=" "
        )const{
            out << start<<delim;
            out<< cargo_on ;
            out<<   to_type_textable(_cargo);
            out<<    cargo_off;
            for(const auto& [k,v]: _map) {
                //out
                out << kon << to_type_textable(k) << koff << delim << von
                <<  v
                //to_type_textable(v)
                << voff << delim;
            }
            if (_psuper && (!plimit || plimit!= _psuper))
                _psuper->write( out, plimit, kon,koff,von, voff,start, end, delim);
            out << end<<delim;
            return out;
        }

    };





    
}
