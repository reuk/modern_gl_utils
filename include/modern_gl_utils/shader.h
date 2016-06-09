#pragma once

#include "bindable.h"

#include <OpenGL/gl3.h>

#include <stdexcept>
#include <string>

template <GLuint type>
class Shader : public IndexOwner {
public:
    Shader()
            : IndexOwner(glCreateShader(type)) {
        if (get_index() == 0) {
            throw std::runtime_error("failed to create shader");
        }
    }

    virtual ~Shader() {
        glDeleteShader(get_index());
    }

    Shader(const Shader &rhs) = delete;
    void operator=(const Shader &rhs) = delete;

    Shader(Shader &&rhs) noexcept = default;
    Shader &operator=(Shader &&rhs) noexcept = default;

    void source(const std::string &src) const {
        auto ptr = src.c_str();
        glShaderSource(get_index(), 1, &ptr, nullptr);
    }

    void compile() const {
        glCompileShader(get_index());
    }
};

using VertexShader = Shader<GL_VERTEX_SHADER>;
using FragmentShader = Shader<GL_FRAGMENT_SHADER>;
