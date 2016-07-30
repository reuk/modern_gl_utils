#pragma once

#include <OpenGL/gl3.h>
#include <functional>
#include <memory>

namespace mglu {

class gl_resource_handle {
public:
    using constructor_func = std::function<void(GLuint&)>;
    using releaser_func = std::function<void(GLuint)>;
    gl_resource_handle(GLuint handle, const releaser_func& releaser);
    gl_resource_handle(const constructor_func& constructor,
                       const releaser_func& releaser);
protected:
    ~gl_resource_handle() noexcept;

public:
    gl_resource_handle(const gl_resource_handle&) = delete;
    gl_resource_handle& operator=(const gl_resource_handle&) = delete;

    gl_resource_handle(gl_resource_handle&& rhs) noexcept;
    gl_resource_handle& operator=(gl_resource_handle&& rhs) noexcept;

    void swap(gl_resource_handle& rhs) noexcept;

    GLuint get_handle() const;
    bool valid() const;

private:
    GLuint handle;
    releaser_func releaser;
};

//----------------------------------------------------------------------------//

class bindable : public gl_resource_handle {
public:
    class scoped final {
    public:
        scoped(const bindable& t);
        ~scoped() noexcept;

    private:
        const bindable& t;
    };

    using gl_resource_handle::gl_resource_handle;

    bindable(bindable&&) noexcept = default;
    bindable& operator=(bindable&&) noexcept = default;

    void bind() const;
    void unbind() const;

protected:
    ~bindable() noexcept = default;

private:
    virtual void do_bind(GLuint) const = 0;
};

bindable::scoped get_scoped(const bindable& u);

class usable : public gl_resource_handle {
public:
    class scoped final {
    public:
        scoped(const usable& t);
        ~scoped() noexcept;

    private:
        const usable& t;
    };

    using gl_resource_handle::gl_resource_handle;
    usable(usable&&) noexcept = default;
    usable& operator=(usable&&) noexcept = default;

    void use() const;
    void unuse() const;

protected:
    ~usable() noexcept = default;

private:
    virtual void do_use(GLuint) const = 0;
};

usable::scoped get_scoped(const usable& u);

}  // namespace mglu
