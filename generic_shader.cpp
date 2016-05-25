#include "generic_shader.h"

#define GLM_FORCE_RADIANS
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

GenericShader::GenericShader()
        : ShaderProgram(vertex_shader, fragment_shader) {
}

void GenericShader::set_matrix(const std::string &s,
                               const glm::mat4 &mat) const {
    glUniformMatrix4fv(get_uniform_location(s), 1, GL_FALSE, value_ptr(mat));
}

void GenericShader::set_model_matrix(const glm::mat4 &mat) const {
    set_matrix("v_model", mat);
}

void GenericShader::set_view_matrix(const glm::mat4 &mat) const {
    set_matrix("v_view", mat);
}

void GenericShader::set_projection_matrix(const glm::mat4 &mat) const {
    set_matrix("v_projection", mat);
}

void GenericShader::set_black(bool b) const {
    glUniform1i(get_uniform_location("v_black"), b);
}

const std::string GenericShader::vertex_shader(R"(
#version 150
in vec3 v_position;
in vec4 v_color;
out vec4 f_color;
uniform mat4 v_model;
uniform mat4 v_view;
uniform mat4 v_projection;
uniform bool v_black;

const float minPoint = 0.1;
const float maxPoint = 8.0;
const float minColour = 0.9;
const float maxColour = 1.0;
const float maxDist = 20.0;

void main() {
    vec4 cs_Position = v_view * v_model * vec4(v_position, 1.0);
    gl_Position = v_projection * cs_Position;
    float dist = -cs_Position.z;
    float scaled = 1.0 - (dist / maxDist);
    float p = scaled * (maxPoint - minPoint) + minPoint;
    float c = scaled * (maxColour - minColour) + minColour;
    p = clamp(p, minPoint, maxPoint);
    c = clamp(c, minColour, maxColour);
    gl_PointSize = p;
    f_color = v_color * vec4(c);
    f_color = v_black ? vec4(0, 0, 0, 1) : f_color;
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
