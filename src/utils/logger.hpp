#ifndef ASPM_UTILS_LOGGER_HPP
#define ASPM_UTILS_LOGGER_HPP

#include <cstddef>
#include <string>

namespace utils {

using zstring = const char*;

class Logger {        
    public:
        static void verbose(zstring format, ...);
        static void warning(zstring format, ...);
        static void error(zstring format, ...);

        static void print(zstring format, ...);

        static void enable_system_logging();
        
        enum class Verbosity {
            Silent,
            Brief,
            Verbose
        };

        static void set_verbosity(Verbosity);

    private:
        inline static Verbosity verbosity = Verbosity::Brief;
        inline static bool system_logging = false;
};

};

#endif