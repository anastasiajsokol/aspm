#include "logger.hpp"

#include <libintl.h>
#include <syslog.h>
#include <stdarg.h>
#include <cstdio>

using utils::Logger;

void Logger::verbose(zstring format, ...){
    if(verbosity == Logger::Verbosity::Verbose){
        va_list args;
        va_start(args, format);
        std::fputs("aspm: ", stdout);
        std::vprintf(format, args);
        std::putc('\n', stdout);
        va_end(args);
    }
}

void Logger::warning(zstring format, ...){
    if(verbosity != Logger::Verbosity::Silent){
        va_list args;
        va_start(args, format);
        std::fprintf(stderr, "aspm: (%s) ", gettext("warning"));
        std::vfprintf(stderr, format, args);
        std::putc('\n', stderr);
        va_end(args);

        if(system_logging){
            va_start(args, format);
            vsyslog(LOG_WARNING, format, args);
            va_end(args);
        }
    }
}

void Logger::error(zstring format, ...){
    if(verbosity != Logger::Verbosity::Silent){
        va_list args;
        va_start(args, format);
        std::fprintf(stderr, "aspm: (%s) ", gettext("error"));
        std::vfprintf(stderr, format, args);
        std::putc('\n', stderr);
        va_end(args);

        if(system_logging){
            va_start(args, format);
            vsyslog(LOG_ERR, format, args);
            va_end(args);
        }
    }
}

void Logger::print(zstring format, ...){
    if(verbosity != Logger::Verbosity::Silent){
        va_list args;
        va_start(args, format);
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