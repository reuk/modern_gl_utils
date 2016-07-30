#include "modern_gl_utils/quad_shader.h"

namespace mglu {

QuadShader::QuadShader()
        : program(Program::from_sources(vertex_shader, fragment_shader)) {
}

const char* QuadShader::vertex_shader(R"(
#version 330
layout(location = 0) in vec3 v_position;
out vec2 UV;
void main() {
    gl_Position = vec4(v_position, 1.0);
    UV = (v_position.xy + vec2(1, 1)) / 2.0;
}
)");

const char* QuadShader::fragment_shader(R"(
#version 330
in vec2 UV;
layout(location = 0) out vec4 frag_color;
uniform sampler2D f_texture;
void main() {
    frag_color = texture(f_texture, UV);
}
)");

}  // namespace mglu