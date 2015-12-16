#pragma once

#include <GL/glew.h>

#include "bindable.h"

#include <vector>

class Texture: public Bindable {
public:
    Texture();
    virtual ~Texture();

    void do_bind(GLuint) const override;
    void data(GLsizei w, GLsizei h, GLubyte* t) const;
};
