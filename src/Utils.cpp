#include "Utils.hpp"

bool str_to_bool(std::string str) {
    bool ret;
    std::istringstream(str) >> std::boolalpha >> ret;
    return ret;
}

