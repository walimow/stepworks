#pragma once

#include <string>
#include <type_traits>
#include  <utility>
#include  <typeinfo>

namespace stepworks::first{
   
    
//todo typeinfo +option <int>
//impl: info, typeinfo    

const int write_type_info_name =1;    
    
template <typename T, typename = void>
struct has_member_to_text
        : std::false_type
{};


template <typename T>
struct has_member_to_text<T,
std::void_t<decltype(std::declval<T>().to_text( 1  ))>>
        : std::true_type
{};
    
namespace internal{
    
    template <typename T>
std::string to_text(const T& x, const int& opt=0)
{
    if constexpr(std::is_same_v<T, std::string>) {
        return x;                  // statement invalid, if no conversion to string
    }
    else
//      if constexpr(std::is_same_v<decltype(std::declval<const T&>().to_text( opt )), std::string>){
        if constexpr(has_member_to_text<T>()) {
            return x.to_text(opt);
        }
        else if constexpr(std::is_arithmetic_v<T>) {
            auto svalue = std::to_string(x);
            if (opt==1){
              std::string type_name = typeid(T).name();
              svalue = "<"+type_name+"> "+svalue+ " ";
            }               
            return svalue;  // statement invalid, if x is not numeric
        }
        else {
            return std::string(x);     // statement invalid, if no conversion to string
        }
}


    
}    
    
    
    
template <typename Ta, int option=0>
struct to_typetext{
    //constexpr is not literal type
    std::string f1( const Ta& a)const { 
      return     internal::to_text( a, option); 
}
    std::string f0()const {         return "(nothing)";    }
    
  template<typename Any> 
    std::string ft0(const Any&)const {         return "(nothing) ...todo: typeinfo...";    }

};
  


    
}
