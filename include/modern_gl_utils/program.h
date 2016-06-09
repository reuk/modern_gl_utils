#pragma once

#include "shader.h"
#include "bindable.h"

#include "glm/glm.hpp"

#include <string>

class Program : public Usable {
public:
    Program();
    virtual ~Program();

    template <GLuint I>
    void attach(const Shader<I> &s) {
        glAttachShader(get_index(), s.get_index());
    }

    template <GLuint I>
    void detach(const Shader<I> &s) {
        glDetachShader(get_index(), s.get_index());
    }

    void link() ;
    void do_use(GLuint) override;

    GLint get_attrib_location(const std::string &name) const;
    GLint get_uniform_location(const std::string &name) const;

    bool check() const;
    bool verify() const;

    void set(const std::string& name, GLfloat) ;
    void set(const std::string& name, GLfloat, GLfloat) ;
    void set(const std::string& name, GLfloat, GLfloat, GLfloat) ;
    void set(const std::string& name, GLfloat, GLfloat, GLfloat, GLfloat) ;

    void set(const std::string& name, GLint) ;
    void set(const std::string& name, GLint, GLint) ;
    void set(const std::string& name, GLint, GLint, GLint) ;
    void set(const std::string& name, GLint, GLint, GLint, GLint) ;

    void set(const std::string& name, glm::vec2) ;
    void set(const std::string& name, glm::vec3) ;
    void set(const std::string& name, glm::vec4) ;

    void set(const std::string& name, glm::ivec2) ;
    void set(const std::string& name, glm::ivec3) ;
    void set(const std::string& name, glm::ivec4) ;

    void set(const std::string& name, const glm::mat4&) ;
};
