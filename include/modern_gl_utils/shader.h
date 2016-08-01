#pragma once

#include "bindable.h"

#include <OpenGL/gl3.h>

#include <stdexcept>
#include <string>

namespace mglu {

template <GLuint type>
class shader final {
public:
    shader()
            : handle(glCreateShader(type), [](auto i) { glDeleteShader(i); }) {
    }

    void source(const std::string &src) const {
        auto ptr = src.c_str();
        glShaderSource(get_handle(), 1, &ptr, nullptr);
    }

    void compile() const {
        glCompileShader(get_handle());
        iv_throw_if_false<GL_COMPILE_STATUS>();
    }

    template <GLenum flag>
    auto get_iv() const {
        return checking::get_shader_iv<flag>(get_handle());
    }

    template<GLenum flag>
    void iv_throw_if_false() const {
        checking::shader_iv_throw_if_false<flag>(get_handle());
    }

    auto get_handle() const {
        return handle.get_handle();
    }

    std::string get_info_log() const {
        return checking::get_shader_info_log(get_handle());
    }

private:
    gl_resource_handle handle;
};

using vertex_shader = shader<GL_VERTEX_SHADER>;
using fragment_shader = shader<GL_FRAGMENT_SHADER>;

}  // namespace mglu
