#include "modern_gl_utils/vao.h"

namespace mglu {

VAO::VAO()
        : bindable([](auto& i) { glGenVertexArrays(1, &i); },
                   [](auto i) { glDeleteVertexArrays(1, &i); }) {
}

void VAO::do_bind(GLuint index) const {
    glBindVertexArray(index);
}

}  // namespace mglu
