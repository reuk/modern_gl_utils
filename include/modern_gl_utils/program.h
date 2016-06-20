#pragma once

#include "bindable.h"
#include "shader.h"

#include "glm/glm.hpp"

#include <string>

namespace mglu {

class Program : public Usable {
public:
    Program();
    virtual ~Program();

    template <GLuint I>
    void attach(const Shader<I>& s) const {
        glAttachShader(get_index(), s.get_index());
    }

    template <GLuint I>
    void detach(const Shader<I>& s) const {
        glDetachShader(get_index(), s.get_index());
    }

    void link() const;
    void do_use(GLuint) const override;

    GLint get_attrib_location(const std::string& name) const;
    GLint get_uniform_location(const std::string& name) const;

    bool check() const;
    bool verify() const;

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
};

}  // namespace mglu
