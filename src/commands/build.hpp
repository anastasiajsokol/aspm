#ifndef ASPM_COMMANDS_BUILD_HPP
#define ASPM_COMMANDS_BUILD_HPP

#include <optional>
#include <string>

#include "directory.hpp"

namespace aspm {

void build(
    path root,
    path shell,
    path out,
    std::optional<path> installer,
    std::string name,
    std::string version,
    bool allow_broken
);

};

#endif