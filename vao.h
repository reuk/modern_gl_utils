#pragma once

#include "bindable.h"

#include <OpenGL/gl3.h>

class VAO : public Bindable {
public:
    VAO();
    virtual ~VAO();

    void do_bind(GLuint) const override;
};
