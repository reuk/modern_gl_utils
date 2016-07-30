#pragma once

#include "program.h"

namespace mglu {

class QuadShader final {
public:
    QuadShader();

private:
    static const char* vertex_shader;
    static const char* fragment_shader;

    Program program;
};

}  // namespace mglu
