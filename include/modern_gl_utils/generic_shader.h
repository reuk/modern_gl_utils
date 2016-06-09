#pragma once

#include "shader_program.h"

#include "glm/glm.hpp"

class GenericShader : public ShaderProgram {
public:
    GenericShader();

    void set_model_matrix(const glm::mat4 &mat) const;
    void set_view_matrix(const glm::mat4 &mat) const;
    void set_projection_matrix(const glm::mat4 &mat) const;

private:
    static const std::string vertex_shader;
    static const std::string fragment_shader;
};
