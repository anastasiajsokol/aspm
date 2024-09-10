/**
 *  Все счастливые семьи похожи друг на друга,
 *  каждая несчастливая семья несчастлива по-своему.
 *      - Лев Николаевич Толстой
**/

#ifndef ASPM_UTILS_EXIT_HPP
#define ASPM_UTILS_EXIT_HPP

namespace utils {

using exit_type = unsigned char;

namespace exit {

// replaces EXIT_SUCCESS, show that all is ok
constexpr exit_type SUCCESS = 0;

// generic failure, prefer using a specific code (or making a new one)
constexpr exit_type FAILURE = 1;

// as an exit code this means command line arguments
// as a return code may mean function arguments
constexpr exit_type INVALID_ARGUMENTS = 2;

// insufficent system permissions to perform an action
// should be returned based on errno
constexpr exit_type INSUFFICENT_PERMISSIONS = 3;

};

};

#endif