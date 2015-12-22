#include "vao.h"

VAO::VAO()
        : Bindable(0) {
    glGenVertexArrays(1, &index);
}

VAO::~VAO() {
    glDeleteVertexArrays(1, &index);
}

void VAO::do_bind(GLuint index) const {
    glBindVertexArray(index);
}
