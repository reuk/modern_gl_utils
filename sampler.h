#pragma once

#include <GL/glew.h>

#include <vector>

class Sampler {
public:
    Sampler();
    virtual ~Sampler();

    void bind(GLuint where) const;
    static void unbind();
    GLuint get_index() const;
    void parameter_i(GLuint, GLuint) const;

private:
    GLuint index;
};
