#include "shader_program.h"

#include <string>

ShaderProgram::ShaderProgram(const std::string & vs, const std::string & fs) {
    FragmentShader f;
    f.source(fs);
    f.compile();

    VertexShader v;
    v.source(vs);
    v.compile();

    attach(f);
    attach(v);
    link();
}
