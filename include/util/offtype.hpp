#pragma once

namespace stepworks{
    namespace types{
    
//the left of the extendeable optional type 
struct off_info {
    //former 'atom' off 
    long code{ 0 };
    int severity{ 0 };
    std::string _msg;
};     


template <typename Off=off_info>
using off_handler_void = void(*)(const Off&);

}}

