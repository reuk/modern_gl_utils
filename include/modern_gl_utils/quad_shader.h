#pragma once

#include "program.h"

namespace mglu {

class quad_shader final {
public:
    quad_shader();

private:
    static const char* vertex_shader;
    static const char* fragment_shader;

    program program;
};

}  // namespace mglu
