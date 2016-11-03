#pragma once

#include "quad_shader.h"
#include "vao.h"
#include "buffer_object.h"

#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtx/rotate_vector.hpp"

namespace mglu {

class screen_quad final {
public:
    screen_quad(const program& shader);

    void draw() const;

private:
    vao vao;
    static_vbo vertex_bo;
};

}  // namespace mglu
