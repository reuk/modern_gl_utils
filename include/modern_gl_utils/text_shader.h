#pragma once

#include "program.h"
#include "texture.h"

#include "glm/glm.hpp"

namespace mglu {

class TextShader final {
public:
    TextShader();
    void set_tex(GLint i) const;

private:
    static const char* vertex_shader;
    static const char* fragment_shader;

    Program program;
};

}  // namespace mglu