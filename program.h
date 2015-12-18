#pragma once

#include "logger.h"
#include "shader.h"
#include "bindable.h"

#include <string>

class Program : public Usable {
public:
    Program();
    virtual ~Program();

    template <GLuint I>
    void attach(const Shader<I> &s) const {
        glAttachShader(index, s.get_index());
    }

    template <GLuint I>
    void detach(const Shader<I> &s) const {
        glDetachShader(index, s.get_index());
    }

    void link() const;
    void do_use(GLuint) const override;

    GLint get_attrib_location(const std::string &name) const;
    GLint get_uniform_location(const std::string &name) const;

    bool check() const;
    bool verify() const;
};
