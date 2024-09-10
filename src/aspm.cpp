#include "utils/logger.hpp"
#include "utils/exit.hpp"

int main(void){
    utils::Logger::print("hello world from aspm!\n");
    return utils::exit::SUCCESS;
}