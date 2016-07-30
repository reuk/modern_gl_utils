#pragma once

#include <OpenGL/gl3.h>

#include "bindable.h"
#include "render_buffer.h"
#include "texture_object.h"

namespace mglu {

template <GLuint mode>
class FBO final : public bindable {
public:
    FBO()
            : bindable([](auto& i) { glGenFramebuffers(1, &i); },
                       [](auto i) { glDeleteFramebuffers(1, &i); }) {
    }

    void depthbuffer(const DepthBuffer& buffer) const {
        glFramebufferRenderbuffer(GL_FRAMEBUFFER,
                                  GL_DEPTH_STENCIL_ATTACHMENT,
                                  GL_RENDERBUFFER,
                                  buffer.get_handle());
    }

    void texture(const TextureObject& texture, GLenum attachment) const {
        glFramebufferTexture(
            GL_FRAMEBUFFER, attachment, texture.get_handle(), 0);
    }

private:
    void do_bind(GLuint index) const override {
        glBindFramebuffer(mode, index);
    }
};

using ReadDrawFBO = FBO<GL_FRAMEBUFFER>;
using ReadFBO = FBO<GL_READ_FRAMEBUFFER>;
using DrawFBO = FBO<GL_DRAW_FRAMEBUFFER>;

}  // namespace mglu
