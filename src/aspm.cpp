#include <cstdlib>
#include <cstdio>

#include "utils/exit.hpp"

int main(void){
    std::puts("hello from aspm!");
    return unwrap(utils::Exit::Success);
}