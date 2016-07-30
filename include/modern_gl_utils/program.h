#pragma once

#include "bindable.h"
#include "shader.h"

#include "glm/glm.hpp"

#include <string>

namespace mglu {

class Program final : public usable {
public:
    Program();
    Program(Program&&) noexcept = default;
    Program& operator=(Program&&) noexcept = default;
    virtual ~Program();

    template <GLuint I>
    void attach(const Shader<I>& s) const {
        glAttachShader(get_handle(), s.get_handle());
    }

    template <GLuint I>
    void detach(const Shader<I>& s) const {
        glDetachShader(get_handle(), s.get_handle());
    }

    void link() const;

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

    static Program from_sources(const char* fs, const char* vs) {
        FragmentShader f;
        f.source(fs);
        f.compile();

        VertexShader v;
        v.source(vs);
        v.compile();

        Program p;
        p.attach(f);
        p.attach(v);
        p.link();
        return p;
    }

private:
    void do_use(GLuint) const override;
};

}  // namespace mglu
