#pragma once

#include "bindable.h"

#include <OpenGL/gl3.h>

#include <stdexcept>
#include <string>

namespace mglu {

template <GLuint type>
class Shader final {
public:
    Shader()
            : handle(glCreateShader(type), [](auto i) { glDeleteShader(i); }) {
        if (!handle.valid()) {
            throw std::runtime_error("failed to create shader");
        }
    }

    Shader(const Shader &rhs) = delete;
    void operator=(const Shader &rhs) = delete;

    Shader(Shader &&rhs) noexcept = default;
    Shader &operator=(Shader &&rhs) noexcept = default;

    void source(const std::string &src) const {
        auto ptr = src.c_str();
        glShaderSource(handle.get_handle(), 1, &ptr, nullptr);
    }

    void compile() const {
        glCompileShader(handle.get_handle());
    }

    constexpr auto get_handle() const {
        return handle.get_handle();
    }

private:
    gl_resource_handle handle;
};

using VertexShader = Shader<GL_VERTEX_SHADER>;
using FragmentShader = Shader<GL_FRAGMENT_SHADER>;

}  // namespace mglu