#include "logger.hpp"

#include <libintl.h>
#include <syslog.h>
#include <stdarg.h>
#include <cstdio>

using utils::Logger;

void Logger::verbose(zstring format, ...){
    if(verbosity == Logger::Verbosity::Verbose){
        // start variadic argument list
        va_list args;
        va_start(args, format);

        // standard program id header
        std::fputs("aspm: ", stdout);
        
        // print to stdout
        std::vprintf(format, args);

        // final newline
        // a newline in format would be bad form for the syslog functions
        std::putc('\n', stdout);

        // make sure to cleanup variadic argument list
        va_end(args);
    }
}

void Logger::warning(zstring format, ...){
    // warnings may be turned off by setting verbosity to silent
    if(verbosity != Logger::Verbosity::Silent){
        // start variadic argument list
        va_list args;
        va_start(args, format);

        // print standard prefix with warning tag (internationalized)
        // TODO: option to turn off internationalization of logging tags
        std::fprintf(stderr, "aspm: (%s) ", gettext("warning"));

        // print the provided message
        std::vfprintf(stderr, format, args);
        
        // end with a final newline
        // bad form to place newlines in syslog so this encourages not placing them in format
        std::putc('\n', stderr);

        // cleanup variadic arguments
        va_end(args);

        if(system_logging){
            // log to syslog if system logging is enabled
            // making sure to restart the variadic list
            va_start(args, format);
            vsyslog(LOG_WARNING, format, args);
            va_end(args);
        }
    }
}

void Logger::error(zstring format, ...){
    // errors may be turned off by setting verbosity to silent
    if(verbosity != Logger::Verbosity::Silent){
        // initialize variadic arguments
        va_list args;
        va_start(args, format);

        // print aspm program header with error tag
        // TODO: option to turn off internationalization of logging tags
        std::fprintf(stderr, "aspm: (%s) ", gettext("error"));

        // print the message
        std::vfprintf(stderr, format, args);

        // end with a newline
        // bad form to place newline in format for syslog
        std::putc('\n', stderr);

        // cleanup varadic argument list
        va_end(args);

        if(system_logging){
            // log to system if system logging is enabled
            // make sure to restart variadic argument list
            va_start(args, format);
            vsyslog(LOG_ERR, format, args);
            va_end(args);
        }
    }
}

void Logger::print(zstring format, ...){
    // only print if not silent
    if(verbosity != Logger::Verbosity::Silent){
        va_list args;
        va_start(args, format);

        // here format should probably end in a newline
        // not really a logging function
        std::vprintf(format, args);
        
        va_end(args);
    }
}

void Logger::enable_system_logging(){
    if(!system_logging){
        // open the logging handle with
        //      name: aspm
        //      flags: fallback to console, open now (before chroot!)
        //      facility: user program
        openlog("aspm", LOG_CONS | LOG_NDELAY, LOG_USER);

        system_logging = true;
    }
}

void Logger::set_verbosity(Logger::Verbosity value){
    verbosity = value;
}