#include "modern_gl_utils/geometry_helpers.h"

#include <algorithm>

std::vector<GLushort> indices(int points) {
    std::vector<GLushort> ret(points);
    auto i = 0;
    std::generate(begin(ret), end(ret), [&i]() { return i++; });
    return ret;
}

std::vector<GLfloat> format(const std::vector<glm::vec3> &points) {
    std::vector<GLfloat> ret(points.size() * 3);
    for (auto i = 0u; i != points.size(); ++i) {
        auto ret_index = i * 3;
        ret[ret_index + 0] = points[i].x;
        ret[ret_index + 1] = points[i].y;
        ret[ret_index + 2] = points[i].z;
    }
    return ret;
}
