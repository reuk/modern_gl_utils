#pragma once

#include "bindable.h"

class TextureObject : public Bindable {
public:
    TextureObject()
            : Bindable(0) {
        glGenTextures(1, &index);
    }

    virtual ~TextureObject() {
        glDeleteTextures(1, &index);
    }

    void do_bind(GLuint index) const {
        glBindTexture(GL_TEXTURE_2D, index);
    }

    void image(glm::ivec2 size) const {
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

    void parameter(GLenum pname, GLint param) const {
        glTexParameteri(GL_TEXTURE_2D, pname, param);
    }

    void parameter(GLenum pname, GLfloat param) const {
        glTexParameterf(GL_TEXTURE_2D, pname, param);
    }
};
