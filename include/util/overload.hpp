//
// Created by karsten on 18.10.21.
//

#ifndef STEPWORKS_OVERLOAD_HPP
#define STEPWORKS_OVERLOAD_HPP

template<class... Ts> struct overload : Ts... { using Ts::operator()...; };
template<class... Ts> overload(Ts...) -> overload<Ts...>;


#endif //STEPWORKS_OVERLOAD_HPP
