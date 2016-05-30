#include "modern_gl_utils/vao.h"

VAO::VAO()
        : Bindable(0) {
    glGenVertexArrays(1, &get_index());
}

VAO::~VAO() {
    glDeleteVertexArrays(1, &get_index());
}

void VAO::do_bind(GLuint index) const {
    glBindVertexArray(index);
}
