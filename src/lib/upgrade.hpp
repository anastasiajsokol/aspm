#ifndef ASPM_LIB_UNINSTALL_HPP
#define ASPM_LIB_UNINSTALL_HPP

#include "directory.hpp"

namespace aspm {

void upgrade(
    path root,
    path stripped,
    path package,
    bool overwrite,
    bool ignore_hash,
    bool strict,
    bool allow_downgrade,
    bool safe
);

};

#endif