#ifndef ASPM_COMMANDS_UNINSTALL_HPP
#define ASPM_COMMANDS_UNINSTALL_HPP

#include "../utils/directory.hpp"

namespace aspm {

void upgrade(
    utils::path root,
    utils::path stripped,
    utils::path package,
    bool overwrite,
    bool ignore_hash,
    bool strict,
    bool allow_downgrade,
    bool safe
);

};

#endif