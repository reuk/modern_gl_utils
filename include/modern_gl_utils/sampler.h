#pragma once

#include "bindable.h"

#include <vector>

class Sampler : public Bindable {
public:
    Sampler();
    Sampler(GLuint where);
    virtual ~Sampler();

    void set_where(GLuint where);
    GLuint get_where() const;

    void do_bind(GLuint) const override;

    void parameter_i(GLuint, GLuint) const;

private:
    GLuint where;
};
