#ifndef ASPM_UTILS_LOGGER_HPP
#define ASPM_UTILS_LOGGER_HPP

#include <cstddef>
#include <string>

namespace utils {

using zstring = const char*;

class Logger {        
    public:
        /**
         *   Displays the message with standard program id if verbosity is set to verbose
         * 
         *  @param format will be passed to a variation of std::printf
         *  @note does not print to system log even if system logging is enabled
         *  @note ideally format should not include any newlines
        **/
        static void verbose(zstring format, ...);

        /**
         *   Prints a warning to stderr with an prefix of 'aspm: (warning)' unless the verbosity is set to silent
         * 
         *  @param format will be passed to a variation of std::printf
         *  @note prints to the system log if system logging is enabled
         *  @note ideally format should not include any newlines
        **/
        static void warning(zstring format, ...);

        /**
         *   Prints an error to stderr with an prefix of 'aspm: (error)' unless the verbosity is set to silent
         * 
         *  @param format will be passed to a variation of std::printf
         *  @note prints to the system log if system logging is enabled
         *  @note ideally format should not include any newlines
        **/
        static void error(zstring format, ...);

        /**
         *   Prints to console as-is unless verbosity is set to silent
         * 
         *  @param format will be passed to a variation of std::printf
         *  @note does not print any additional content
         *  @note should probably at least have an ending newline
        **/
        static void print(zstring format, ...);

        /**
         *  Opens a handle to the system log and tells the warning and error functions to use it
         *  
         *  @warning must be called before entering a chroot environment
        **/
        static void enable_system_logging();
        
        enum class Verbosity {
            Silent,
            Brief,
            Verbose
        };

        /**
         *  Sets the verbosity level for logging functions
         * 
         *  @note silent: do not print anything ever
         *  @note brief: (default) do not print verbose messages
         *  @note verbose: print everything
        **/
        static void set_verbosity(Verbosity);

    private:
        inline static Verbosity verbosity = Verbosity::Brief;
        inline static bool system_logging = false;
};

};

#endif