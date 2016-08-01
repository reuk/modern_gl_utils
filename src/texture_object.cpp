#include "modern_gl_utils/texture_object.h"

namespace mglu {

texture_object::texture_object()
        : bindable([](auto& i) { glGenTextures(1, &i); },
                   [](auto i) { glDeleteTextures(1, &i); }) {
}

void texture_object::image(glm::ivec2 size) const {
    //  TODO probably a better place to put this
    glTexImage2D(GL_TEXTURE_2D,
                 0,
                 GL_RGBA,
                 size.x,
                 size.y,
                 0,
                 GL_RGBA,
                 GL_UNSIGNED_BYTE,
                 nullptr);
}

void texture_object::parameter(GLenum pname, GLint param) const {
    glTexParameteri(GL_TEXTURE_2D, pname, param);
}

void texture_object::parameter(GLenum pname, GLfloat param) const {
    glTexParameterf(GL_TEXTURE_2D, pname, param);
}

void texture_object::do_bind(GLuint index) const {
    glBindTexture(GL_TEXTURE_2D, index);
}

}  // namespace mglu
