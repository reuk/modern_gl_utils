#pragma once

#include "program.h"

namespace mglu {

class ShaderProgram : public Program {
public:
    ShaderProgram(const std::string &vs, const std::string &fs);
};

}  // namespace mglu
