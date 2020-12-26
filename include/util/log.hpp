//
// Created by kh on 20.12.20.
//

#ifndef STEPWORKS_LOG_HPP
#define STEPWORKS_LOG_HPP

#include <iostream>
#include <chrono>
#include <string>
#include <cstdlib>
#include <sstream>
#include <cstring>
#include <fstream>
#include <iomanip>
#include <memory>
#include <cassert>

namespace stepworks::util{

    struct logging_support{
        std::unique_ptr< std::ostream> _oost;
        std::filebuf fb;
        bool logon = false;
        bool with_time =false;
        std::string _delim= " ";


        template<class Ty, class ...Rest>
        std::ostream& out( Ty&& a, Rest&&...rest){
            assert(_oost);
            std::ostream& _ost = *_oost;
            _ost << std::forward<Ty>(a) << _delim;
            out( std::forward<Rest>(rest) ... ) ; //... <<( std::forward<Rest> (rest) );
            return _ost;
        }

        template< class ...Args>
        std::ostream& output( Args&&...rest){
            if (logon) {

                assert(_oost);
                std::ostream &_ost = *_oost;
                if (with_time) {
                    auto rnow = std::time(nullptr);
                    _ost <<
                    std::asctime(std::localtime(
                            &rnow
                            )) << _delim;   ///chrono::system_clock::now()<<'\t';
                }
                out(std::forward<Args>(rest) ...);
                _ost << std::endl;
                return _ost;
            }
            else
                return std::cout; ///dummy
        }


            template<class Ty>
        std::ostream& out( Ty&& a){
            assert(_oost);
            std::ostream& _ost = *_oost;
            _ost << std::forward<Ty>(a)  ; //... <<( std::forward<Rest> (rest) );
            return _ost;
        }


        template<class ...Args>
        std::ostream& operator()(Args&&...args){
                    if (logon){
                        assert(_oost);
                        std::ostream& _ost = *_oost;
      //                  _ost<<'\n';
                        if (with_time){
                            auto  rnow=std::time(nullptr);
                            _ost<< std::asctime(std::localtime( &rnow ));   ///chrono::system_clock::now()<<'\t';
                        }
                            _ost << _delim << ( std::forward<Args>( args)<<...);
                 //       out(args...);

                        return _ost;
                    }
                return  std::cout;  //sonst dummy...
                }
        explicit operator std::ostream& () const{
            assert(logon);
            return  *_oost;
        }
        bool init_logging(const std::string& name ="stwlogging", bool dt_in_name=true);
        void flush(){
            if (_oost)
                _oost->flush();
        }
        ~logging_support(){
            flush();
        }
    };

    bool logging_support::init_logging(const std::string& name , bool dt_in_name){
        try {
            auto *stw_log_path = getenv("STW_LOG_PATH");   ////   STW_LOG_PATH   must be defined in env!
                if (stw_log_path && *stw_log_path) {
                    flush(); ///maybe
                    std::ostringstream ost;
                    ost << (const char *) stw_log_path;
                    if (stw_log_path[strlen(stw_log_path)-1]!='/')
                        ost <<'/';
                    ost<<name<<'.';
                    if (dt_in_name) {
                        auto tmpr= std::time(nullptr);
                       auto * n = std::localtime (&tmpr );
                       if (n){
                           ost<< std::setfill('0')
                            << std::setw(4)<< n->tm_year
                            << std::setw(2)<<n->tm_mon
                           << std::setw(2)<<n->tm_mday
                           << std::setw(2)<<n->tm_hour
                           << std::setw(2)<<n->tm_min
                           << std::setw(2)<<n->tm_sec;
                       }
                    }
                    ost<< "log";

                    fb.open( ost.str(), std::ios::out);
                    _oost .reset( new std::ostream (&fb));
                    //_oost->open(&fb);
                    return true;
                }
        }catch(...){  }
        return  false;
    }

    static logging_support& global_logging_support(){
        static logging_support loggings_g;
        return loggings_g;
    }

    static bool  reset_global_logging(const std::string lognameroot="stw.logging", bool with_dt=true){
        auto b = global_logging_support().init_logging(lognameroot, with_dt);
        global_logging_support().logon=b;
        return b;
    }

}


#endif //STEPWORKS_LOG_HPP
