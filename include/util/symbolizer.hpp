//
// Created by kh on 13.01.21.
//

#ifndef STEPWORKS_SYMBOLIZER_HPP
#define STEPWORKS_SYMBOLIZER_HPP

#include <map>
#include <set>
#include <vector>
#include <string>
#include <string>

namespace stepworks::util{

template <typename I=int, I minimum=1>
class symbolizer{
public :
    using sym_map_t = std::map< std::string,  I>;

    I _i=0;
    sym_map_t   _symmap;
    std::map<I,std::string> _i2s;
    //std::set<I>  _syms;

    symbolizer()=default;
    symbolizer(std::map<std::string,  I> m): _symmap(m){
        for (const auto& kv: m)
            if (kv.second)
                _i2s [kv.second] = kv.first;
     }
    inline I next(){
        auto x =  _i  ?  _i +1 : minimum;
        _i = x;
        return  _i;
    }
};



template < typename I=int,
           template<typename ...> typename L =  std::vector,
                   I minimal=1
                            >
auto
        symbolize(  const std::string&s,
                    symbolizer<I,minimal>&& sym_ = symbolizer<I,minimal>{},
                    L<I> l=  L<I>{}
                    )
           ->std::pair<symbolizer<I,minimal>, L<I> >
        {
    auto sym = std::move(sym_);
    auto it = sym._symmap.find(s);
    if (it == sym._symmap.end()){
        auto n = sym.next();
        sym._i2s[n]=s;
        sym._symmap[s] =n;
        l.push_back(n);
    }else
        l.push_back(it->second);
    return std::make_pair(sym,l);
}

}




#endif //STEPWORKS_SYMBOLIZER_HPP
