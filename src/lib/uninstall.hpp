#ifndef ASPM_LIB_UNINSTALL_HPP
#define ASPM_LIB_UNINSTALL_HPP

#include "directory.hpp"

namespace aspm {

void uninstall(
    path root,
    path package,
    bool ignore_hash,
    bool strict,
    bool safe
);

};

#endif