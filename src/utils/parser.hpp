#ifndef ASPM_UTILS_PARSER_HPP
#define ASPM_UTILS_PARSER_HPP

#include <variant>
#include <string>

namespace utils {

struct Version {
    
};

struct Arguments {
    std::string command;
    std::string verbose;
    bool safe;
};

};

#endif