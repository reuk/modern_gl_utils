#include "modern_gl_utils/program.h"

#include "glm/gtc/type_ptr.hpp"

#include <map>
#include <vector>

namespace mglu {

program::program()
        : usable(glCreateProgram(), [](auto i) { glDeleteProgram(i); }) {
}

void program::link() const {
    glLinkProgram(get_handle());
    iv_throw_if_false<GL_LINK_STATUS>();
}

void program::do_use(GLuint index) const {
    glUseProgram(index);
}

GLint program::get_attrib_location(const std::string& name) const {
    auto ret = glGetAttribLocation(get_handle(), name.c_str());
    if (ret == -1) {
        throw exceptions::no_such_attribute("program: no such attribute");
    }
    return ret;
}

GLint program::get_uniform_location(const std::string& name) const {
    auto ret = glGetUniformLocation(get_handle(), name.c_str());
    if (ret == -1) {
        throw exceptions::no_such_uniform("program: no such uniform");
    }
    return ret;
}

bool program::valid() const {
    glValidateProgram(get_handle());
    return get_iv<GL_VALIDATE_STATUS>();
}

void program::validate() const {
    glValidateProgram(get_handle());
    iv_throw_if_false<GL_VALIDATE_STATUS>();
}

void program::set(const std::string& name, GLfloat a) const {
    glUniform1f(get_uniform_location(name), a);
}
void program::set(const std::string& name, GLfloat a, GLfloat b) const {
    glUniform2f(get_uniform_location(name), a, b);
}
void program::set(const std::string& name,
                  GLfloat a,
                  GLfloat b,
                  GLfloat c) const {
    glUniform3f(get_uniform_location(name), a, b, c);
}
void program::set(
    const std::string& name, GLfloat a, GLfloat b, GLfloat c, GLfloat d) const {
    glUniform4f(get_uniform_location(name), a, b, c, d);
}

void program::set(const std::string& name, GLint a) const {
    glUniform1i(get_uniform_location(name), a);
}
void program::set(const std::string& name, GLint a, GLint b) const {
    glUniform2i(get_uniform_location(name), a, b);
}
void program::set(const std::string& name, GLint a, GLint b, GLint c) const {
    glUniform3i(get_uniform_location(name), a, b, c);
}
void program::set(
    const std::string& name, GLint a, GLint b, GLint c, GLint d) const {
    glUniform4i(get_uniform_location(name), a, b, c, d);
}

void program::set(const std::string& name, glm::vec2 a) const {
    glUniform2fv(get_uniform_location(name), 1, glm::value_ptr(a));
}
void program::set(const std::string& name, glm::vec3 a) const {
    glUniform3fv(get_uniform_location(name), 1, glm::value_ptr(a));
}
void program::set(const std::string& name, glm::vec4 a) const {
    glUniform4fv(get_uniform_location(name), 1, glm::value_ptr(a));
}

void program::set(const std::string& name, glm::ivec2 a) const {
    glUniform2iv(get_uniform_location(name), 1, glm::value_ptr(a));
}
void program::set(const std::string& name, glm::ivec3 a) const {
    glUniform3iv(get_uniform_location(name), 1, glm::value_ptr(a));
}
void program::set(const std::string& name, glm::ivec4 a) const {
    glUniform4iv(get_uniform_location(name), 1, glm::value_ptr(a));
}

void program::set(const std::string& name, const glm::mat4& a) const {
    glUniformMatrix4fv(
        get_uniform_location(name), 1, GL_FALSE, glm::value_ptr(a));
}

program program::from_sources(const char* vs, const char* fs) {
    fragment_shader f;
    f.source(fs);
    f.compile();

    vertex_shader v;
    v.source(vs);
    v.compile();

    program p;
    p.attach(f);
    p.attach(v);
    p.link();
    return p;
}

std::string program::get_info_log() const {
    return checking::get_program_info_log(get_handle());
}

}  // namespace mglu
