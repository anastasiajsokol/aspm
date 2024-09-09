#ifndef ASPM_COMMANDS_BUILD_HPP
#define ASPM_COMMANDS_BUILD_HPP

#include <optional>
#include <string>

#include "../utils/directory.hpp"

namespace aspm {

void build(
    utils::path root,
    utils::path shell,
    utils::path out,
    std::optional<utils::path> installer,
    std::string name,
    std::string version,
    bool allow_broken
);

};

#endif