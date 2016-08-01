#pragma once

#include "program.h"
#include "texture.h"

#include "glm/glm.hpp"

namespace mglu {

class text_shader final {
public:
    text_shader();
    void set_tex(GLint i) const;

private:
    static const char* vertex_shader;
    static const char* fragment_shader;

    program program;
};

}  // namespace mglu
