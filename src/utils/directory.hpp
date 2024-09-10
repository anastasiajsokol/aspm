#ifndef ASPM_UTILS_DIRECTORY_HPP
#define ASPM_UTILS_DIRECTORY_HPP

#include <filesystem>
#include <optional>

#include "exit.hpp"

namespace utils {

using path = std::filesystem::path;

/**
 *  Attempts to create a temporary directory in the provided base directory
 * 
 *  @param base path to prefered temporary directory (default = /tmp)
 *  @return path to the new directory if successful
**/
std::optional<path> create_temporary_directory(path base = "/tmp");

/**
 *  Attempts to delete the directory at the provided path
 *  
 *  @param directory path to the directory that should be deleted
 *  @return aspm exit_type (see exit.hpp)
**/
exit_type delete_directory(path directory);

/**
 *  Attempts to create an overlay mount using the provided directories
 * 
 *  @param merge directory to mount into the overlay
 *  @param upper this is the directory that will contain any modifications
 *  @param lower this is the directory that is "simulated" or overlayed
 *  @param work may be used to store temporary state
 *  @return aspm standard exit_type
**/
exit_type create_overlay(path merge, path upper, path lower, path work);

};

#endif