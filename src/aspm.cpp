#include <cstdlib>
#include <cstdio>

#include "lib/directory.hpp"
#include "lib/logger.hpp"

int main(void){
    aspm::Logger::set_log_display_level(aspm::LogLevel::Verbose);
    
    std::puts("Hello World");

    auto directory = aspm::create_temporary_directory();

    if(directory){
        aspm::Logger::log(aspm::LogLevel::Verbose, "main", directory.value().c_str());
        aspm::delete_directory(directory.value());
    }

    return EXIT_SUCCESS;
}