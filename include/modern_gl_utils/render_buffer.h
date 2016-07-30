#pragma once

#include "bindable.h"

#include "glm/glm.hpp"
#include <OpenGL/gl3.h>

namespace mglu {

template <GLuint mode>
class RenderBuffer final : public bindable {
public:
    RenderBuffer()
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

using DepthBuffer = RenderBuffer<GL_DEPTH_STENCIL>;

}  // namespace mglu
