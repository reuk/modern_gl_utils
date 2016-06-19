#pragma once

#include "bindable.h"

#include <OpenGL/gl3.h>

namespace mglu {

class VAO : public Bindable {
public:
    VAO();
    virtual ~VAO();

    VAO(VAO&&) noexcept = default;
    VAO& operator=(VAO&&) noexcept = default;

    void do_bind(GLuint) const override;
};

}  // namespace mglu
