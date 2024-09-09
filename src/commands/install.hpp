#ifndef ASPM_COMMANDS_INSTALL_HPP
#define ASPM_COMMANDS_INSTALL_HPP

#include "../utils/directory.hpp"

namespace aspm {

void install(
    utils::path root,
    utils::path package,
    bool overwrite,
    bool safe
);

};

#endif