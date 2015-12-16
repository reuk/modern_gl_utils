#pragma once

#include <GL/glew.h>

class IndexOwner {
public:
    IndexOwner(GLuint index);
    virtual ~IndexOwner() noexcept = default;
    GLuint index;
};

class Bindable : public IndexOwner {
public:
    using IndexOwner::IndexOwner;
    virtual ~Bindable() noexcept = default;

    virtual void do_bind(GLuint) const = 0;

    void bind() const;
    void unbind() const;
};

class Usable : public IndexOwner {
public:
    using IndexOwner::IndexOwner;
    virtual ~Usable() noexcept = default;

    virtual void do_use(GLuint) const = 0;

    void use() const;
    void unuse() const;
};
