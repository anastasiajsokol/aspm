#ifndef ASPM_COMMANDS_INSTALL_HPP
#define ASPM_COMMANDS_INSTALL_HPP

#include "directory.hpp"

namespace aspm {

void install(
    path root,
    path package,
    bool overwrite,
    bool safe
);

};

#endif