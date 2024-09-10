#include <libintl.h>
#include <cstring>

#include "commands/commands.hpp"

#include "utils/logger.hpp"
#include "utils/exit.hpp"

int main(void){
    // print message
    utils::Logger::print(gettext("hello world from aspm!\n"));

    // exit successfully
    return utils::exit::SUCCESS;
}