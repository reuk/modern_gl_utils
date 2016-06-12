#pragma once

#include "bindable.h"

#include <vector>

class Sampler : public Bindable {
public:
    Sampler();
    virtual ~Sampler();

    void set_where(GLuint where);

    void do_bind(GLuint) const override;

    void parameter_i(GLuint, GLuint) const;

private:
    GLuint where;
};
