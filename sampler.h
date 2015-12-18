#pragma once

#include "bindable.h"

#include <vector>

class Sampler : public Bindable {
public:
    Sampler();
    virtual ~Sampler();

    void set_where(GLuint where);

    void bind(GLuint) const;
    void parameter_i(GLuint, GLuint) const;

private:
    GLuint where;
};
