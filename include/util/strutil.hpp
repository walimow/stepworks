#pragma once



#include <iostream>
#include <string>
#include <cctype>
#include <cwctype>
#include <stdexcept>

#include <algorithm>

#include <locale>

using namespace std;

///thanks to /.

namespace stepworks::util {

void to_upper(basic_string<char>& s) {
    for (basic_string<char>::iterator p = s.begin();
            p != s.end(); ++p) {
        *p = toupper(*p); // toupper is for char
    }
}

void to_upper(basic_string<wchar_t>& s) {
    for (basic_string<wchar_t>::iterator p = s.begin();
            p != s.end(); ++p) {
        *p = towupper(*p); // towupper is for wchar_t
    }
}

void to_lower(basic_string<char>& s) {
    for (basic_string<char>::iterator p = s.begin();
            p != s.end(); ++p) {
        *p = tolower(*p);
    }
}

void to_lower(basic_string<wchar_t>& s) {
    for (basic_string<wchar_t>::iterator p = s.begin();
            p != s.end(); ++p) {
        *p = towlower(*p);
    }
}
/////////


// trim from start (in place)
static inline void ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int ch) {
        return !std::isspace(ch);
    }));
}

// trim from start (in place)
    static inline auto ltrim_view(std::string &s) ->std::string_view {
        std::size_t itStart= 0;
        auto sz= s.length();
        while (itStart < sz && isspace( s.at(itStart))){
            itStart++;
        }
        return std::string_view (&s[itStart], sz-itStart);
    }

    static inline auto ltrim_view(const std::string_view &s) ->std::string_view {
        std::size_t itStart= 0;
        auto sz= s.length();
        while (itStart < sz && isspace( s.at(itStart))){
            itStart++;
        }
        return std::string_view (&s[itStart], sz-itStart);
    }


    static inline auto rtrim_view(const std::string &s) ->std::string_view {
        int len= 0;
        if (s.length()){
            len = s.length()-1;
            while (len >=0 && isspace( s.at(len)))
                len--;
            len++;
        }
        return std::string_view (&s[0], len );
    }

    static inline auto rtrim_view(std::string_view s) ->std::string_view {
        int len= 0;
        if (s.length()){
            len = s.length()-1;
            while (len >=0 && isspace( s.at(len)))
                len--;
            len++;
        }
        return std::string_view (&s[0], len );
    }

    static inline auto trim_view(const std::string &s) ->std::string_view {
        return ltrim_view(rtrim_view(s ));
    }

    static inline auto trim_view(std::string_view s) ->std::string_view {
        return ltrim_view(rtrim_view(s) );
    }

    // trim from end (in place)
static inline void rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch) {
        return !std::isspace(ch);
    }).base(), s.end());
}

// trim from both ends (in place)
static inline void trim(std::string &s) {
    ltrim(s);
    rtrim(s);
}

// trim from start (copying)
static inline std::string ltrim_copy(std::string s) {
    ltrim(s);
    return s;
}

// trim from end (copying)
static inline std::string rtrim_copy(std::string s) {
    rtrim(s);
    return s;
}

// trim from both ends (copying)
static inline std::string trim_copy(std::string s) {
    trim(s);
    return s;
}

}
