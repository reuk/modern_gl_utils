#pragma once

#include "bindable.h"

#include <vector>

namespace mglu {

class texture final : public bindable {
public:
    texture();

    void data(GLsizei w, GLsizei h, GLubyte* t) const;

private:
    void do_bind(GLuint) const override;
};

}  // namespace mglu
