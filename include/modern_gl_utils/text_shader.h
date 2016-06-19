#pragma once

#include "shader_program.h"
#include "texture.h"

#include "glm/glm.hpp"

namespace mglu {

class TextShader : public ShaderProgram {
public:
    TextShader();
    void set_tex(GLint i) const;

private:
    static const std::string vertex_shader;
    static const std::string fragment_shader;
};

}  // namespace mglu
