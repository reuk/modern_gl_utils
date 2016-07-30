#include "modern_gl_utils/text_shader.h"

namespace mglu {

TextShader::TextShader()
        : program(Program::from_sources(vertex_shader, fragment_shader)) {
}

void TextShader::set_tex(GLint i) const {
    program.set("f_tex", i);
}

const char* TextShader::vertex_shader(R"(
#version 330
in vec2 v_position;
in vec2 v_uv;
out vec2 f_uv;
void main() {
    gl_Position = vec4(v_position, 0.0, 1.0);
    f_uv = v_uv;
}
)");

const char* TextShader::fragment_shader(R"(
#version 330
in vec2 f_uv;
out vec4 frag_color;
uniform sampler2D f_tex;
void main() {
    frag_color = vec4(vec3(1.0), texture(f_tex, f_uv).r) * vec4(1.0, 1.0, 1.0, 1.0);
}
)");

}  // namespace mglu