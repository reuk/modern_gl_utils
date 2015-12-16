#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "render_buffer.h"
#include "texture_object.h"

template <GLuint mode>
class FBO {
public:
    FBO()
            : index(0) {
        glGenFramebuffers(1, &index);
    }

    virtual ~FBO() {
        glDeleteFramebuffers(1, &index);
    }

    void bind() const {
        glBindFramebuffer(mode, index);
    }

    static void unbind() {
        glBindFramebuffer(mode, 0);
    }

    GLuint get_index() const {
        return index;
    }

    void depthbuffer(const DepthBuffer& buffer) const {
        glFramebufferRenderbuffer(GL_FRAMEBUFFER,
                                  GL_DEPTH_STENCIL_ATTACHMENT,
                                  GL_RENDERBUFFER,
                                  buffer.get_index());
    }

    void texture(const TextureObject& texture, GLenum attachment) const {
        glFramebufferTexture(
            GL_FRAMEBUFFER, attachment, texture.get_index(), 0);
    }

private:
    GLuint index;
};

using ReadDrawFBO = FBO<GL_FRAMEBUFFER>;
using ReadFBO = FBO<GL_READ_FRAMEBUFFER>;
using DrawFBO = FBO<GL_DRAW_FRAMEBUFFER>;
