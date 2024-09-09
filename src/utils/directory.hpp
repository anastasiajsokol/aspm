#ifndef ASPM_UTILS_DIRECTORY_HPP
#define ASPM_UTILS_DIRECTORY_HPP

#include <filesystem>
#include <optional>
#include <cerrno>

namespace aspm {

using path = std::filesystem::path;

// attempts to create a temporary directory in the provided base directory
std::optional<path> create_temporary_directory(path base = "/tmp");

// attempts to delete the directory at the provided path
// on success returns zero, on failure returns -1
int delete_directory(path);

};

#endif