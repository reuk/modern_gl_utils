#pragma once

#include "bindable.h"

#include <vector>

class Texture : public Bindable {
public:
    Texture();
    virtual ~Texture();

    void do_bind(GLuint) override;
    void data(GLsizei w, GLsizei h, GLubyte* t) ;
};
