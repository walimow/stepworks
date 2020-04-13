//
// Created by kh on 10.04.20.
//

#ifndef STEPWORKS_IOX_HPP
#define STEPWORKS_IOX_HPP

namespace stepworks::iox{


    template  <typename T>
    auto to_type_textable(const T& v){
        return v;// std::to_string(v);
    };


    template  <typename T>
    auto to_type_textable(const std::unique_ptr<T> v){
        return "======";
    }

    template <typename...>     struct ost_t;



    //template <typename  stream_t = std::ostream ,  typename mark_t=std::string    >
    template <>
    struct  ost_t<std::ostream, std::string>
    {
        std::ostream& _output= std::cout;
        std::string _start, _end;

        template <typename Ty>
        auto& out(const Ty& o){
            _output << _start<< to_type_textable(o) <<_end;
            return *this;
        }
        auto& kout(const std::string& k){
            _output << k;
            return *this;
        }
        template <typename Ty>
        auto& kout(const std::string& k, const Ty& o){
            _output << k << to_type_textable(o) ;
            return *this;
        }


    };




}


#endif //STEPWORKS_IOX_HPP
