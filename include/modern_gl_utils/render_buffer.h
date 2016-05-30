#pragma once

#include "bindable.h"

#include <OpenGL/gl3.h>

#include <glm/glm.hpp>

template <GLuint mode>
class RenderBuffer : public Bindable {
public:
    RenderBuffer()
            : Bindable(0) {
        glGenRenderbuffers(1, &get_index());
    }

    virtual ~RenderBuffer() {
        glDeleteRenderbuffers(1, &get_index());
    }

    void do_bind(GLuint index) const {
        glBindRenderbuffer(GL_RENDERBUFFER, index);
    }

    void storage(glm::ivec2 size) {
        glRenderbufferStorage(GL_RENDERBUFFER, mode, size.x, size.y);
    }
};

using DepthBuffer = RenderBuffer<GL_DEPTH_STENCIL>;
