#pragma once

#include "bindable.h"

#include "glm/glm.hpp"

namespace mglu {

class texture_object final : public bindable {
public:
    texture_object();

    void image(glm::ivec2 size) const;
    void parameter(GLenum pname, GLint param) const;
    void parameter(GLenum pname, GLfloat param) const;

private:
    void do_bind(GLuint index) const override;
};

}  // namespace mglu
