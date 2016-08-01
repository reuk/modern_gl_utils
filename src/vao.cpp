#include "modern_gl_utils/vao.h"

namespace mglu {

vao::vao()
        : bindable([](auto& i) { glGenVertexArrays(1, &i); },
                   [](auto i) { glDeleteVertexArrays(1, &i); }) {
}

void vao::enable_vertex_attrib_array(GLuint i) const {
    bind();
    glEnableVertexAttribArray(i);
    check_for_gl_error();
}

void vao::disable_vertex_attrib_array(GLuint i) const {
    bind();
    glDisableVertexAttribArray(i);
}

void vao::do_bind(GLuint index) const {
    glBindVertexArray(index);
}

}  // namespace mglu
