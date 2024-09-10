#ifndef ASPM_COMMANDS_COMMANDS_HPP
#define ASPM_COMMANDS_COMMANDS_HPP

#include <filesystem>
#include <string>

namespace commands {

using path = std::filesystem::path;
using zstring = const char*;

void version_with_arguments(int argc, zstring argv[]);
void help_with_arguments(int argc, zstring argv[]);
void list_with_arguments(int argc, zstring argv[]);
void build_with_arguments(int argc, zstring argv[]);
void strip_with_arguments(int argc, zstring argv[]);
void install_with_arguments(int argc, zstring argv[]);
void uninstall_with_arguments(int argc, zstring argv[]);
void upgrade_with_arguments(int argc, zstring argv[]);

void version(path prefix);
void help(path prefix);
void list(path prefix, path root);
void build(path tarball, std::string name, std::string version, path out, path root, path shell, path installer, bool allow_broken);
void strip(path package, path out);
void install(path package, path root, bool overwrite);
void uninstall(path stripped, path root, bool ignore_hash, bool strict);
void upgrade(std::string name, path package, path root, bool overwrite, bool ignore_hash, bool strict, bool allow_downgrade);

};

#endif