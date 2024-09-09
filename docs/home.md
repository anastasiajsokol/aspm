# The ASPM "home" Directory

The ASPM "home" directory is located at "PREFIX/etc/aspm", where PREFIX is specified by the configuration script before building `aspm`.

The directory is layed out via the following layout

    PREFIX/etc/aspm:
        installed:
            list.csv
            $STRIPPED
        config.toml
        aspm.strip
        LISCENSE
        VERSION
        HELP

The `installed` subdirectory holds a csv file with the following format:

    name,version,stripped

Then all of the different stripped package files for installed packages.

The `config.toml` file has varius configuration options that are as-of-yet not specified. It will likely include whether or not `aspm` is bootstrapped and options to override environment variables.

The `aspm.strip` is just the stripped package file for `aspm`. This file only exists if `aspm` is bootstrapped.

The `LISCENSE` file has a copy of the GPL-3.0 license.

The `VERSION` file holds the output of the command `aspm version`.

The `HELP` file is similar to `VERSION`, in that it holds the output of `aspm help`.