
#pragma once
#include <map>
#include <unordered_map>

namespace stepworks{
    //super as const
    //contains an additional particle (as 'cargo')
    template <class Cargo,class K, class T, 
    class  Compare= std::less<K>,  
    class Allocator = std::allocator<std::pair<const K, T> > >
    struct hmapx{
        Cargo _cargo;   
        using Map=std::map<K,T,Compare, Allocator> ;
        const hmapx * _psuper=nullptr;
        Map  _map;
        
        std::pair< typename Map::iterator, int > select (const K&k, int level=0){
            auto it = _map.find(k);
            return it != _map.end() ? 
                 std::make_pair(it, level)
                 :
                 _psuper ? _psuper->select(k, level+1) : std::make_pair(it, -1);
        }
    };
    
}
