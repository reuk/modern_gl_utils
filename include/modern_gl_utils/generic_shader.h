#pragma once

#include "program.h"

#include "glm/glm.hpp"

namespace mglu {

class GenericShader final {
public:
    GenericShader();

    void set_model_matrix(const glm::mat4 &mat) const;
    void set_view_matrix(const glm::mat4 &mat) const;
    void set_projection_matrix(const glm::mat4 &mat) const;

private:
    static const char *vertex_shader;
    static const char *fragment_shader;

    Program program;
};

}  // namespace mglu