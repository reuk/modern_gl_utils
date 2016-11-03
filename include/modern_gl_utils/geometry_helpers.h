#pragma once

#include "glm/glm.hpp"
#include <OpenGL/gl3.h>

#include <vector>
#include <numeric>

namespace mglu {

template<typename T>
std::vector<T> compute_indices(size_t num) {
    std::vector<T> ret(num);
    std::iota(ret.begin(), ret.end(), 0);
    return ret;
}

}  // namespace mglu
