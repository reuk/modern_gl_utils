#pragma once

#include "bindable.h"

#include <vector>

namespace mglu {

class Sampler final : public bindable {
public:
    Sampler();
    Sampler(GLuint where);
    virtual ~Sampler();

    void set_where(GLuint where);
    GLuint get_where() const;

    void parameter_i(GLuint, GLuint) const;

private:
    void do_bind(GLuint) const override;

    GLuint where;
};

}  // namespace mglu
