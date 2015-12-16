#pragma once

#include "vec.h"

#include <vector>

template <typename T>
std::vector<T> concat(const std::vector<Vec3<T>>& vec) {
    std::vector<T> ret;
    for (const auto& i : vec)
        i.for_each([&ret](const auto& j) { ret.push_back(j); });
    return ret;
}
