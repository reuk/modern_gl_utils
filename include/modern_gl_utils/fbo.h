#pragma once

#include <OpenGL/gl3.h>

#include "bindable.h"
#include "render_buffer.h"
#include "texture_object.h"

template <GLuint mode>
class FBO : public Bindable {
public:
    FBO()
            : Bindable(0) {
        glGenFramebuffers(1, &get_index());
    }

    virtual ~FBO() {
        glDeleteFramebuffers(1, &get_index());
    }

    void do_bind(GLuint index) override {
        glBindFramebuffer(mode, index);
    }

    void depthbuffer(const DepthBuffer& buffer) {
        glFramebufferRenderbuffer(GL_FRAMEBUFFER,
                                  GL_DEPTH_STENCIL_ATTACHMENT,
                                  GL_RENDERBUFFER,
                                  buffer.get_index());
    }

    void texture(const TextureObject& texture, GLenum attachment) {
        glFramebufferTexture(
            GL_FRAMEBUFFER, attachment, texture.get_index(), 0);
    }
};

using ReadDrawFBO = FBO<GL_FRAMEBUFFER>;
using ReadFBO = FBO<GL_READ_FRAMEBUFFER>;
using DrawFBO = FBO<GL_DRAW_FRAMEBUFFER>;
