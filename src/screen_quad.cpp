#include "modern_gl_utils/screen_quad.h"

#include <vector>

namespace mglu {

screen_quad::screen_quad(const program& shader) {
    vertex_bo.data(std::vector<glm::vec3>{{-1, -1, 0},
                                          {1, -1, 0},
                                          {-1, 1, 0},
                                          {-1, 1, 0},
                                          {1, -1, 0},
                                          {1, 1, 0}});

    auto s_vao = vao.get_scoped();
    enable_and_bind_buffer(
        vao, vertex_bo, shader.get_attrib_location("v_position"), 3, GL_FLOAT);
}

void screen_quad::draw() const {
    auto s_vao = vao.get_scoped();
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

}  // namespace mglu
