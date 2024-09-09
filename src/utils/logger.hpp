#ifndef ASPM_UTILS_LOGGER_HPP
#define ASPM_UTILS_LOGGER_HPP

#include <cstddef>
#include <string>

namespace utils {

enum class LogLevel {
    Debug,
    Verbose,
    Notice,
    Warning,
    Error,
    Alert,
    Emergency,
};

class Logger {
    private:
        // baseline console log level
        inline static LogLevel baseline = LogLevel::Notice;

        // whether or not syslog should be called
        inline static bool log_to_system = false;
        
    public:
        // general purpose log function
        static void log(LogLevel level, const char* caller, const char *message);

        // set private baseline variable
        static void set_log_display_level(LogLevel);

        // turn on system logging
        // WARNING: must be called before chroot
        static void enable_system_logging();

        // turn off system logging
        static void disable_system_logging();
};

};

#endif