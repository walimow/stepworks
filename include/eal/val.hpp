//
// Created by kh on 23.08.20.
//

#ifndef STEPWORKS_LET_HPP
#define STEPWORKS_LET_HPP

#include <utility>

namespace stepworks::eal::fo {

    template<typename Ty>
    class _val_{
        Ty _value;
    public:
        _val_(Ty&&v):_value(std::move(v)){};
        const auto& operator()()const { return  _value; }
    };

    template<typename Ty>
    auto val(Ty&& v ){
        return  _val_<Ty>{ std::forward<Ty>(v) };
    }


}

#endif //STEPWORKS_LET_HPP
