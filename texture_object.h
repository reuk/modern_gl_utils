#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class TextureObject {
public:
    TextureObject()
            : index(0) {
        glGenTextures(1, &index);
    }

    virtual ~TextureObject() {
        glDeleteTextures(1, &index);
    }

    void bind() const {
        glBindTexture(GL_TEXTURE_2D, index);
    }

    static void unbind() {
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    GLuint get_index() const {
        return index;
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

private:
    GLuint index;
};
