#include "texture.h"

using namespace std;

Texture::Texture()
        : Bindable(0) {
    glGenTextures(1, &index);
}

Texture::~Texture() {
    glDeleteTextures(1, &index);
}

void Texture::do_bind(GLuint index) const {
    glBindTexture(GL_TEXTURE_2D, index);
}

void Texture::data(GLsizei w, GLsizei h, GLubyte* t) const {
    auto s = get_scoped();
    glTexImage2D(GL_TEXTURE_2D, 0, GL_R8, w, h, 0, GL_RED, GL_UNSIGNED_BYTE, t);
}
