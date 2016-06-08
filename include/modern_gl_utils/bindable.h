#pragma once

#include <memory>
#include <OpenGL/gl3.h>

class IndexOwner {
public:
    IndexOwner(GLuint index);
    virtual ~IndexOwner() noexcept = default;

    IndexOwner(IndexOwner&&) noexcept;
    IndexOwner& operator=(IndexOwner&&) noexcept;

    IndexOwner(const IndexOwner&) noexcept = delete;
    IndexOwner& operator=(const IndexOwner&) noexcept = delete;

    bool valid() const;
    const GLuint &get_index() const;
    GLuint& get_index();

private:
    GLuint index {0};
};

class Bindable : public IndexOwner {
public:
    struct Scoped {
        Scoped(const Bindable& t);
        virtual ~Scoped() noexcept;

    private:
        const Bindable& t;
    };

    using IndexOwner::IndexOwner;
    Bindable(Bindable&&) noexcept = default;
    Bindable& operator=(Bindable&&) noexcept = default;

    virtual void do_bind(GLuint) const = 0;

    void bind() const;
    void unbind() const;

    Scoped get_scoped() const;
};

class Usable : public IndexOwner {
public:
    struct Scoped {
        Scoped(const Usable& t);
        virtual ~Scoped() noexcept;

    private:
        const Usable& t;
    };

    using IndexOwner::IndexOwner;
    Usable(Usable&&) noexcept = default;
    Usable& operator=(Usable&&) noexcept = default;

    virtual void do_use(GLuint) const = 0;

    void use() const;
    void unuse() const;

    Scoped get_scoped() const;
};
