#pragma once

#include <GL/glew.h>

template <GLuint mode>
class RenderBuffer {
public:
    RenderBuffer()
            : index(0) {
        glGenRenderbuffers(1, &index);
    }

    virtual ~RenderBuffer() {
        glDeleteRenderbuffers(1, &index);
    }

    void bind() const {
        glBindRenderbuffer(GL_RENDERBUFFER, index);
    }

    static void unbind() {
        glBindRenderbuffer(GL_RENDERBUFFER, 0);
    }

    GLuint get_index() const {
        return index;
    }

    void storage(glm::ivec2 size) {
        glRenderbufferStorage(GL_RENDERBUFFER, mode, size.x, size.y);
    }

private:
    GLuint index;
};

using DepthBuffer = RenderBuffer<GL_DEPTH_STENCIL>;
