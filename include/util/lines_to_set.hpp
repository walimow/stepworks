#pragma once

#include <iostream>
#include <fstream>
#include <set>
#include <string>
#include <list>

#include <util/strutil.hpp>


struct lines_to_set {
    std::set<std::string> _container;
    bool _trim=true;
    bool _lower=true;
    lines_to_set(const std::string&  path ) {

        std::filebuf fb;

        if (fb.open(path, std::ios::in))
        {
            std::istream ist(&fb);
            while (ist/*.good() && !ist.eof()*/ ) {
                std::string s;
                ist>>s;
                if (_trim)
                    stepworks::util::trim(s);
                if (_lower)
                    stepworks::util::to_lower(s);
                _container.insert(s);
            }
        }
        ////test
        else{
            std::cerr<<"\npath not found: "<< path;
        }
    }
};
