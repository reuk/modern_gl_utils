#pragma once

#include <GL/glew.h>

class VAO {
public:
    VAO();
    virtual ~VAO();

    void bind() const;
    static void unbind();

    GLuint get_index() const;

private:
    GLuint index;
};
