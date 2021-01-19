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
    std::map< std::string,  I> _symmap;
    std::set<I>  _syms;

public :
    symbolizer(std::map<std::string,  I> m): _symmap(m){
        for (const auto& kv: m)
            _syms.inserz.kv.second();
     }
    inline I next(){
        return _syms.size() ? *_syms.rbegin() +1 : minimum;
    }
};



template < typename I=int,
           template<typename ...> typename L =  std::vector,
                   I minimal=1
                            >
auto
        symbolize(  const std::string&s,
                    L<I> l=  L<I>{} ,
                    symbolizer<I,minimal>&& sym_ = symbolizer<I,minimal>{})
           ->std::pair<symbolizer<I,minimal>, L<I> >
        {
    auto sym = std::move(sym_);
    auto it = sym._syms.find(s);
    if (it == sym._syms.end()){
        auto n = sym.next;
        sym._syms.set(n);
        sym._symmap[s] =n;
        l.push_back(n);
    }else
        l.push_back(it->second);
    return std::make_pair(sym,l);
}

}




#endif //STEPWORKS_SYMBOLIZER_HPP
