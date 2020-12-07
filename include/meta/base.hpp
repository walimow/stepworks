//
// Created by karsten on 29.05.20.
//

#ifndef STEPWORKS_BASE_HPP
#define STEPWORKS_BASE_HPP

#include <string>
#include <vector>
#include <typeinfo>

namespace stepworks::meta{

    template <typename...> struct mtyp;

    template <typename Ty>
    struct mtyp<Ty> {

         static std::string name(){ return "atom ("+ std::string(typeid(Ty).name())+")";
             ;}
    };

    template <typename Ty, template <typename ...> typename  Form>
    struct mtyp<Form<Ty>> {
        static std::string  name(){ return "anyform "+
                     std::string(typeid(Form<Ty>).name())+"/"+
        mtyp<Ty>::name();}
    };



    template < template <typename ...> typename  Form, typename ...Els>
    struct mtyp<Form<Els...>> {
        static std::string  name(){ return "anyform: "+
                                           std::string(typeid(Form<Els...>).name())+"/"+
                                           mtyp<Els...>::name();}
    };


    template <typename Ty>
    struct mtyp< std::vector<Ty>> {
        static std::string  name(){ return "vector "+ mtyp<Ty>::name();}
    };

    template <typename Ty, typename ...Rest>
    struct mtyp< Ty, Rest...> {
        static std::string  name(){ return  mtyp<Ty>::name()+":"+mtyp<Rest...>::name();}
    };


    template <typename Ty, typename ...Rest>
    struct mtyp< std::tuple<Ty, Rest...>> {
        static std::string  name(){ return "tuple: "+ mtyp<Ty, Rest...>::name();}
    };


    template <typename Ta, typename Tb>
    struct mtyp< std::pair<Ta, Tb>> {
        static std::string  name(){ return "pair: "+ mtyp<Ta>::name()+", "
            +mtyp<Tb>::name()
        ;}
    };

    template <typename T>
    auto _mname(const T& ){
        return mtyp<T>::name();
    }

}

#endif //STEPWORKS_BASE_HPP
