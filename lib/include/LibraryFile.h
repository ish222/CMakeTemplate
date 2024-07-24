#ifndef __LIBRARYFILE__
#define __LIBRARYFILE__

#include <string>
#include <thread>

// External lib includes to test compilation
#include "boost/algorithm/string.hpp"
#include "rapidjson/document.h"

class Library {
public:
    Library() = default;
    Library(int p_num, std::string p_name);
    virtual ~Library() = default;

    int get_num() const { return _num; }
    std::string get_name() const { return boost::algorithm::to_upper_copy(_name); }

    void set_num(int p_num) { _num = p_num; }
    void set_name(std::string p_name) { _name = p_name; }

    std::string ToString() const;

protected:
    int _num{};
    std::string _name{};
    rapidjson::Document _doc;
    // C++23
    std::jthread _thread;
};

#endif  // __LIBRARYFILE__