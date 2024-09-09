#ifndef ASPM_COMMANDS_UNINSTALL_HPP
#define ASPM_COMMANDS_UNINSTALL_HPP

#include "../utils/directory.hpp"

namespace aspm {

void uninstall(
    utils::path root,
    utils::path package,
    bool ignore_hash,
    bool strict,
    bool safe
);

};

#endif