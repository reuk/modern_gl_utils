#pragma once

#include <OpenGL/gl3.h>

class IndexOwner {
public:
    IndexOwner(GLuint index);
    virtual ~IndexOwner() noexcept = default;
    GLuint index;
};

class Bindable : public IndexOwner {
public:
    struct Scoped {
        Scoped(const Bindable& t)
                : t(t) {
            t.bind();
        }

        virtual ~Scoped() {
            t.unbind();
        }

    private:
        const Bindable& t;
    };

    using IndexOwner::IndexOwner;
    virtual ~Bindable() noexcept = default;

    virtual void do_bind(GLuint) const = 0;

    void bind() const;
    void unbind() const;

    Scoped get_scoped() const;
};

class Usable : public IndexOwner {
public:
    struct Scoped {
        Scoped(const Usable& t)
                : t(t) {
            t.use();
        }

        virtual ~Scoped() {
            t.unuse();
        }

    private:
        const Usable& t;
    };

    using IndexOwner::IndexOwner;
    virtual ~Usable() noexcept = default;

    virtual void do_use(GLuint) const = 0;

    void use() const;
    void unuse() const;

    Scoped get_scoped() const;
};
