#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <sstream>
#include <utility>
#include <vector>

enum MouseKeys {
    LEFT_CLICK = 1,
    RIGHT_CLICK = 3,
};

/* vvv Custom Types vvv */

typedef std::pair<unsigned int, unsigned int> pair_uint;
typedef std::vector<std::vector<bool>> vec_2d_bool;

/* ^^^ Custom Types ^^^ */

/* vvv Utils Functions vvv */

bool str_to_bool(std::string str);

/* ^^^ Utils Functions ^^^ */

#endif

