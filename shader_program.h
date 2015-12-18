#pragma once

#include "program.h"

class ShaderProgram : public Program {
public:
    ShaderProgram(const std::string &vs, const std::string &fs);
};
