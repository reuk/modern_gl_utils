#pragma once

#include <GL/glew.h>

#include "bindable.h"

template <GLuint mode>
class RenderBuffer: public Bindable {
public:
    RenderBuffer()
            : Bindable(0) {
        glGenRenderbuffers(1, &index);
    }

    virtual ~RenderBuffer() {
        glDeleteRenderbuffers(1, &index);
    }

    void do_bind(GLuint index) const {
        glBindRenderbuffer(GL_RENDERBUFFER, index);
    }

    void storage(glm::ivec2 size) {
        glRenderbufferStorage(GL_RENDERBUFFER, mode, size.x, size.y);
    }
};

using DepthBuffer = RenderBuffer<GL_DEPTH_STENCIL>;
