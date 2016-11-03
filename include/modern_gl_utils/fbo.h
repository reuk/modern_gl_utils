#pragma once

#include <OpenGL/gl3.h>

#include "bindable.h"
#include "render_buffer.h"
#include "texture_object.h"

namespace mglu {

template <GLuint mode>
class fbo final : public bindable {
public:
    fbo()
            : bindable([](auto& i) { glGenFramebuffers(1, &i); },
                       [](auto i) { glDeleteFramebuffers(1, &i); }) {
    }

    void depthbuffer(const depth_buffer& buffer) const {
        glFramebufferRenderbuffer(GL_FRAMEBUFFER,
                                  GL_DEPTH_STENCIL_ATTACHMENT,
                                  GL_RENDERBUFFER,
                                  buffer.get_handle());
    }

    void texture(const texture_object& texture, GLenum attachment) const {
        glFramebufferTexture(
            GL_FRAMEBUFFER, attachment, texture.get_handle(), 0);
    }

private:
    void do_bind(GLuint index) const override {
        glBindFramebuffer(mode, index);
    }
};

using read_draw_fbo = fbo<GL_FRAMEBUFFER>;
using read_fbo = fbo<GL_READ_FRAMEBUFFER>;
using draw_fbo = fbo<GL_DRAW_FRAMEBUFFER>;

}  // namespace mglu
