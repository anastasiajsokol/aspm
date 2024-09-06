#include "logger.hpp"

#include <syslog.h>
#include <cstdio>

using aspm::Logger, aspm::LogLevel;

void Logger::log(LogLevel level, const char* caller, const char *message){
    // only print to console if we are within the baseline
    if(level >= baseline){
        // pick stdout or stderr depending on severity
        FILE *console = (level <= LogLevel::Notice) ? stdout : stderr;

        // print log output
        //  - there is no real benefit in checking if this failed
        std::fprintf(console, "aspm: (%s) %s\n", caller, message);
    }
    
    if(log_to_system){
        // also output to syslog to proper priority set
        //  - verbose is mapped to info
        const int priority[] = {
            LOG_DEBUG,
            LOG_INFO,
            LOG_NOTICE,
            LOG_WARNING,
            LOG_ERR,
            LOG_ALERT,
            LOG_EMERG,
        };

        // write to syslog
        syslog(priority[static_cast<unsigned>(level)], "(%s) %s", caller, message);
    }
}

void Logger::set_log_display_level(LogLevel level){
    // WARNING: not thread safe, of course
    baseline = level;
}

void Logger::enable_system_logging(){
    static bool system_log_is_open = false;

    if(!system_log_is_open){
        // prevent the log from being openned again
        // WARNING: not thread safe, of course
        system_log_is_open = true;
        
        // open the log
        //  - set application name to aspm (A Source Package Manager)
        //  - open it now so that we do not fail to open it in chroot later
        //  - open as a normal user process
        openlog("aspm", LOG_NDELAY, LOG_USER);
    }

    // WARNING: not thread safe, of course
    log_to_system = true;
}

void Logger::disable_system_logging(){
    log_to_system = false;
}