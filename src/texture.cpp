#include "modern_gl_utils/texture.h"

namespace mglu {

texture::texture()
        : bindable([](auto& i) { glGenTextures(1, &i); },
                   [](auto i) { glDeleteTextures(1, &i); }) {
}

void texture::do_bind(GLuint index) const {
    glBindTexture(GL_TEXTURE_2D, index);
}

void texture::data(GLsizei w, GLsizei h, GLubyte* t) const {
    auto s = get_scoped();
    glTexImage2D(GL_TEXTURE_2D, 0, GL_R8, w, h, 0, GL_RED, GL_UNSIGNED_BYTE, t);
}

}  // namespace mglu
