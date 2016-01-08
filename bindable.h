#pragma once

#include <memory>
#include <OpenGL/gl3.h>

class IndexOwner {
public:
    IndexOwner(GLuint index);

    virtual ~IndexOwner() noexcept = default;
    IndexOwner(IndexOwner&&) noexcept = default;
    IndexOwner& operator=(IndexOwner&&) noexcept = default;
    IndexOwner(const IndexOwner&) noexcept = default;
    IndexOwner& operator=(const IndexOwner&) noexcept = default;

    GLuint get_index() const;
    GLuint & get_index();

private:
    std::unique_ptr<GLuint> index;
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
    virtual ~Bindable() noexcept = default;

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
    virtual ~Usable() noexcept = default;

    virtual void do_use(GLuint) const = 0;

    void use() const;
    void unuse() const;

    Scoped get_scoped() const;
};
