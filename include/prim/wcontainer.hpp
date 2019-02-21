#pragma once

#include <set>
#include <map>
#include <forward_list>
#include <list>

/// the 'primary' operation

namespace stepworks::primary{
    
    template<typename Ta>
    auto _f_(std::set<Ta>&& d, const Ta& a)->std::set<Ta>{
        std::move(d).insert(a);
        return std::move(d);
    }
        
    template<typename Ta>
    auto _f_(std::set<Ta>&& d, Ta&& a)->std::set<Ta>{
        std::move(d).insert(std::move(a));
        return d;
    }
    
    template<typename K, typename Ta>
    auto _f_(std::map<K,Ta>&& d, const std::pair<K,Ta>& kv)->std::map<K,Ta>{
        std::move(d[kv.first])=kv.second;
        return d;
    }

    
    ////specified, overloaded

    
    ////!!
    template<typename Ta>
    auto _f_(std::forward_list<Ta>& d, const Ta& a)->std::forward_list<Ta>&{
        d.push_front(a);
        return d;
    }
    
    
    ////??
    template<typename Ta>
    auto _f_(std::list<Ta>& d, const Ta& a)->std::list<Ta>&{
        d.push_back(a);
        return d;
    }
    
    template<typename Ta>
    auto _f_(std::list<Ta>&& d, const Ta& a)->std::list<Ta>&{
        std::move(d).push_back(a);
        return std::move(d);
    }
    
     template<typename K, typename Ta>
    auto _f_(std::map<K, std::forward_list<Ta>>&& d, const std::pair<K,Ta>& kv)->std::map<K, std::forward_list<Ta>>{
       // auto && rf = std::move(d)[kv.first];
          _f_ (    std::move(d)[kv.first]  ,    kv.second);
        return std::move(d);
    }

    
    template<typename K, typename Ta>
    auto _f_(std::map<K,Ta>&& d, std::pair<K,Ta>&& kv)->std::map<K,Ta>{
        std::move(d[kv.first])=std::move(kv.second);
        return d;
    }
    
    
    template<typename Ta>
    auto _f_(std::forward_list<Ta>&& d, const Ta& a)->std::forward_list<Ta>{
        std::move(d).push_back(a);
        return d;
    }
    
    template<typename Ta>
    auto _f_(std::forward_list<Ta>&& d, Ta&& a)->std::forward_list<Ta>{
        std::move(d).push_back(std::move(a));
        return d;
    }
    
    ///any listlike
    template<typename Ta, template <typename...> typename L>
    auto _f_   (L<Ta>&& d, const Ta& a)->L<Ta>{
         _f_(  std::move(d),a);
        return std::move(d);
    }
    
}
