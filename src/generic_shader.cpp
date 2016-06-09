#include "modern_gl_utils/generic_shader.h"

#include "glm/gtc/type_ptr.hpp"

GenericShader::GenericShader()
        : ShaderProgram(vertex_shader, fragment_shader) {
}

void GenericShader::set_model_matrix(const glm::mat4 &mat) {
    set("v_model", mat);
}

void GenericShader::set_view_matrix(const glm::mat4 &mat) {
    set("v_view", mat);
}

void GenericShader::set_projection_matrix(const glm::mat4 &mat) {
    set("v_projection", mat);
}

const std::string GenericShader::vertex_shader(R"(
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

const std::string GenericShader::fragment_shader(R"(
#version 150
in vec4 f_color;
out vec4 frag_color;
void main() {
    frag_color = f_color;
}
)");
