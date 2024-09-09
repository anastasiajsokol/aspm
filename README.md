# aspm
A Source Package Manager

Usage: `aspm command (command parameters) (general and command options)`

Any flag will be overwritten by the corresponding environment variable or by conflicting flags located further to the left.

## General Flags

`-v`, `--verbose`

Show additional information about the steps the program is taking. Should be combined with any other command. The environment variable overwrites the flag option. Can be overwritten by `ASPMVERBOSE=[true|verbose]`.

`--brief` (default)

Show the default amount of information. Overwritten by `ASPMVERBOSE=brief`.

`--silent`

Do not output anything to the console or logs. Can be overwritten by `ASPMVERBOSE=silent`.

`--safe` | `--unsafe`

If "safe", perform all commands inside of a temporary overlay directory before committing results to the system if successful. Can be overwrited by `ASPMMODE=[safe|unsafe]`. By default `aspm` runs in "safe" mode, however if a system does not support overlay filesystems (or there is some other reason you want to avoid overlay mounts) unsafe can be used for most commands. However, there is currently no plans to support the `build` command in "unsafe" mode, if you try an error will be generated. If "safe" mode is impossible, you will have to figure out how to create the ASPM binary some other way.

## Commands

`version` | `--version`

Displays information about the current version of `aspm`. It is recommended to use the `version` variation, however `--version` is allowed for compatability with other programs.

`help` | `--help` | `-h`

Displays a slightly modified version of this markdown file.

`list`

List all of the installed packages on the current system. If the `--root path` option is set, or the overriding ASPMROOT environment variable, then the root path will be treated as the system root.

`build` tarpackage

Build the tar package into an ASPM binary package which is required for the other commands. To specify the shell path relative to the root path (set with the `--root path` option, or overriden by the existance of an ASPMROOT environment variable) use the `--shell path` option. By default the script will attempt to run `/bin/sh` from the root path. To provide an installation script for the package you can pass the `--installer script` option to run automatically within the shell. If the result of the installer script is not zero then the build will fail unless the `--allow-broken` flag is set. Otherwise an interactive shell will be created. By default output will be the tarpackage path with the extension replaced by `.pkg`. To specify the output file use the `-o path` option. By default the package will be named after the tarpackage filename without any extensions, to specify a package name use the `--name name` option. To keep track of the installed version, build the package with the `--version version` option, this is recommended but not required.

`strip` binpackage

Remove the actual file content and only stores the file paths and hashes of every file in the package. This is useful for uninstalling the package later, so that you do not have to store two copies of the binaries (one installed, one in the binpackage). When you install a package a stripped package file will be saved to the ASPM directory, `PREFIX/etc/aspm`, which is used for the `uninstall packagename` command variation (`PREFIX` must have been set on the configuration step of building `aspm` itself). By default the file will be formed by appending `.stripped` to the binpackage path, to specify an alternative name use the `-o path` option.

`install` binpackage

Install a built ASPM binary package into a system. By default the current system will be used, however the system root may be specified using the `--root path` option or overriden by the ASPMROOT environment variable. Unless the `--overwrite` flag is set the package will first be checked for file collisions and for package name collisions, if there is a collision an error will be returned and the package will not be installed.

`uninstall` packagename | `uninstall` strippedpackage | `uninstall` binpackage

Uninstall an installed package. Note that dependancies are not checked, and this might break other packages. If packagename is specified (as seen in the output of the `list` command) then the stripped package file stored in `PREFIX/etc/aspm` will be used. If a stripped package is provided then that will be used to uninstall the package. If a binpackage is provided it will first be converted into a stripped package then used. Unless the `--ignore-hash` flag is set, `aspm` will first verify that the file being removed has the hash expected by the stripped package file, if the hash does not match an error will be generated. In safe mode, this means that the package is still installed, in unsafe mode this means that you now have a partially installed package! To catch other potential issues (currently just non-existant files) you can use the `--strict` flag.

`upgrade` binpackage | `upgrade` packagename binpackage | `upgrade` strippedpackage binpackage

If both a package name and a binpackage are specified, the named package will be replaced. Replace an installed package with a new binary package. Usually this is similar to first uninstalling the package then reinstalling it, but an important usecase is bootstrapping `aspm` so that it can track itself. If no version is specified by the binary package, the version tracked by `aspm` will not be changed. The same options provided to both the `install` and `uninstall` commands can be used, and have the same effect. This includes `--root path`, `--overwrite`, `--ignore-hash`, and `--strict`. The only extension is that if `--strict` is set `aspm` will attept to make sure that the new package version is not less than the old package version (ie downgrading). To get the `--strict` behavior without checking version information also pass the `--allow-downgrade` flag.