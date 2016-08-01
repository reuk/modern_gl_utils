#pragma once

#include "bindable.h"

#include "glm/glm.hpp"
#include <OpenGL/gl3.h>

namespace mglu {

template <GLuint mode>
class render_buffer final : public bindable {
public:
    render_buffer()
            : bindable([](auto& i) { glGenRenderbuffers(1, &i); },
                       [](auto i) { glDeleteRenderbuffers(i); }) {
    }

    void storage(glm::ivec2 size) const {
        glRenderbufferStorage(GL_RENDERBUFFER, mode, size.x, size.y);
    }

private:
    void do_bind(GLuint index) const {
        glBindRenderbuffer(GL_RENDERBUFFER, index);
    }
};

using depth_buffer = render_buffer<GL_DEPTH_STENCIL>;

}  // namespace mglu
