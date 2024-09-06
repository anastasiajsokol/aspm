#include <cstdlib>

#include "lib/logger.hpp"

int main(void){
    aspm::Logger::set_log_display_level(aspm::LogLevel::Verbose);
    aspm::Logger::log(aspm::LogLevel::Verbose, "main", "Hello World!");

    return EXIT_SUCCESS;
}