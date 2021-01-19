//
// Created by kh on 27.05.20.
//

#ifndef STEPWORKS_TOSTRX_HPP
#define STEPWORKS_TOSTRX_HPP

#include <sstream>
#include <memory_resource>
#include <detect/detect_tuple.hpp>
//#include <util/
//‘std::__cxx11::basic_string<char>::basic_string(const std::vector<int>&)’
#include <detect/detect_tostring.hpp>
#include <detect/detect_iterable.hpp>

namespace stepworks {


    typedef enum {
        noopt = 0,
        eform = 1,
        eempty = 0, ecomma = 2, ecolon = 4, esemicolon = 6, edelimchar = 6,
        espace = 8
    } formopt;

    template <typename Ty>
    requires (stepworks::detect::supports_tostring<Ty>::value )
    auto to_string(const Ty& a){
        return std::to_string(a);
    }

    static    auto to_string(const std::string& s){
        return s;
    }

    static auto to_string(const std::pmr::string& s){
        return std::string( s);
    }

    template<typename Ty, template<typename ...> typename Form>
    auto to_string(const Form<Ty> &v, int opt_ = 0) {
        int opt = opt_;
        if (!opt)
            opt = ecomma | espace;
        std::ostringstream ost;
//        char adelim[3] = {',', ':', ';'};
        std::string str_delim = "";

        if ((eform & opt) == eform) {

        }
        switch (opt & edelimchar) {
            case ecomma:
                str_delim += ',';
                break;
            case ecolon:
                str_delim += ':';
                break;
            case esemicolon:
                str_delim += ';';
                break;
            default:;
        }
        if ( (opt & espace) == espace)
            str_delim += ' ';

        for (const auto &a: v) {
            ost << a << str_delim;
        }
        return ost.str();
    }

    template<typename Ty, template<typename ...> typename Form, typename Allocator>
///todo requires iterable
    requires ( stepworks::detect::is_forward_iterable< Form<Ty>>::value )
    auto to_string(const Form<Ty, Allocator> &v, int opt_ = 0) {
        int opt = opt_;
        if (!opt)
            opt = ecomma | espace;
        std::ostringstream ost;
        char adelim[3] = {',', ':', ';'};
        std::string str_delim = "";

        if ((eform & opt) == eform) {

        }
        switch (opt & edelimchar) {
            case ecomma:
                str_delim += ',';
                break;
            case ecolon:
                str_delim += ':';
                break;
            case esemicolon:
                str_delim += ';';
                break;
            default:;
        }
        if ((opt & espace)==espace)
            str_delim += ' ';

        for (const auto &a: v) {
            ost << a << str_delim;
        }
        return ost.str();
    }


    template <typename ... Ts>
    std::string to_string(const Ts& ... ts) {
        std::stringstream ss;
        const char* sep = "";
        ((static_cast<void>(ss << sep <<  ts ), sep = " "), ...);    ///the point, where unprintable types occur! (no to_string<X>)
        return ss.str();
    }

    template <typename... Args>
    std::string tuple_to_string(const std::tuple<Args...> &t) {
        return std::apply([](const auto&... ts) { return to_string(ts...); }, t);
    }

    template <typename... Args>
    std::string to_string(const std::tuple<Args...> &t) {
        return tuple_to_string(t);
    }

}



#endif //STEPWORKS_TOSTRX_HPP
