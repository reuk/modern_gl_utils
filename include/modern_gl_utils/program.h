#pragma once

#include "bindable.h"
#include "checking.h"
#include "exceptions.h"
#include "shader.h"

#include "glm/glm.hpp"

#include <string>

namespace mglu {

class program final : public usable {
public:
    program();

    template <GLuint I>
    void attach(const shader<I>& s) const {
        glAttachShader(get_handle(), s.get_handle());
        check_for_gl_error();
    }

    template <GLuint I>
    void detach(const shader<I>& s) const {
        glDetachShader(get_handle(), s.get_handle());
        check_for_gl_error();
    }

    GLint get_attrib_location(const std::string& name) const;
    GLint get_uniform_location(const std::string& name) const;

    void link() const;

    bool valid() const;
    void validate() const;

    void set(const std::string& name, GLfloat) const;
    void set(const std::string& name, GLfloat, GLfloat) const;
    void set(const std::string& name, GLfloat, GLfloat, GLfloat) const;
    void set(const std::string& name, GLfloat, GLfloat, GLfloat, GLfloat) const;

    void set(const std::string& name, GLint) const;
    void set(const std::string& name, GLint, GLint) const;
    void set(const std::string& name, GLint, GLint, GLint) const;
    void set(const std::string& name, GLint, GLint, GLint, GLint) const;

    void set(const std::string& name, glm::vec2) const;
    void set(const std::string& name, glm::vec3) const;
    void set(const std::string& name, glm::vec4) const;

    void set(const std::string& name, glm::ivec2) const;
    void set(const std::string& name, glm::ivec3) const;
    void set(const std::string& name, glm::ivec4) const;

    void set(const std::string& name, const glm::mat4&) const;

    static program from_sources(const char* fs, const char* vs);

    template <GLenum flag>
    auto get_iv() const {
        return checking::get_program_iv<flag>(get_handle());
    }

    template<GLenum flag>
    void iv_throw_if_false() const {
        checking::program_iv_throw_if_false<flag>(get_handle());
    }

    std::string get_info_log() const;

private:
    void do_use(GLuint) const override;
};

namespace exceptions {
class no_such_attribute final : public exception {
public:
    using exception::exception;
};
class no_such_uniform final : public exception {
public:
    using exception::exception;
};
}  // namespace exceptions

}  // namespace mglu
