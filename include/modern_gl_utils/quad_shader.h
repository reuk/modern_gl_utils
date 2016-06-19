#pragma once

#include "shader_program.h"

namespace mglu {

class QuadShader : public ShaderProgram {
public:
    QuadShader();

private:
    static const std::string vertex_shader;
    static const std::string fragment_shader;
};

}  // namespace mglu
