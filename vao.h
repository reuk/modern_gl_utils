#pragma once

#include "bindable.h"

#include <GL/glew.h>

class VAO : public Bindable {
public:
    VAO();
    virtual ~VAO();

    void do_bind(GLuint) const override;
};
