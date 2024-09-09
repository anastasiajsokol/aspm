#ifndef ASPM_UTILS_EXIT_HPP
#define ASPM_UTILS_EXIT_HPP

namespace utils {

enum class Exit : unsigned char {
    Success = 0,
    Failure = 1,
    InvalidArguments = 2,
    InsufficentPermissions = 3,
};

inline unsigned char unwrap(Exit code){
    return static_cast<unsigned char>(code);
}

};

#endif