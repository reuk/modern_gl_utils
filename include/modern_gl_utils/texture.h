#pragma once

#include "bindable.h"

#include <vector>

namespace mglu {

class Texture final : public bindable {
public:
    Texture();
    virtual ~Texture();

    void data(GLsizei w, GLsizei h, GLubyte* t) const;

private:
    void do_bind(GLuint) const override;
};

}  // namespace mglu
