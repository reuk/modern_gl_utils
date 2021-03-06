#include "modern_gl_utils/generic_shader.h"

#include "glm/gtc/type_ptr.hpp"

namespace mglu {

generic_shader::generic_shader()
        : program(program::from_sources(vertex_shader, fragment_shader)) {
}

void generic_shader::set_model_matrix(const glm::mat4 &mat) const {
    program.set("v_model", mat);
}

void generic_shader::set_view_matrix(const glm::mat4 &mat) const {
    program.set("v_view", mat);
}

void generic_shader::set_projection_matrix(const glm::mat4 &mat) const {
    program.set("v_projection", mat);
}

const char *generic_shader::vertex_shader(R"(
#version 150
in vec3 v_position;
in vec4 v_color;
out vec4 f_color;
uniform mat4 v_model;
uniform mat4 v_view;
uniform mat4 v_projection;

void main() {
    gl_Position = v_projection * v_view * v_model * vec4(v_position, 1.0);
    f_color = v_color;
}
)");

const char *generic_shader::fragment_shader(R"(
#version 150
in vec4 f_color;
out vec4 frag_color;
void main() {
    frag_color = f_color;
}
)");

}  // namespace mglu
