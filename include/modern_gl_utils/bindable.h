#pragma once

#include <OpenGL/gl3.h>
#include <functional>
#include <memory>

namespace mglu {

class gl_resource_handle final {
public:
    using constructor_func = std::function<void(GLuint&)>;
    using releaser_func = std::function<void(GLuint)>;

    gl_resource_handle(GLuint handle, const releaser_func& releaser);
    gl_resource_handle(const constructor_func& constructor,
                       const releaser_func& releaser);

    ~gl_resource_handle() noexcept;

    gl_resource_handle(const gl_resource_handle&) = delete;
    gl_resource_handle& operator=(const gl_resource_handle&) = delete;

    gl_resource_handle(gl_resource_handle&& rhs) noexcept;
    gl_resource_handle& operator=(gl_resource_handle&& rhs) noexcept;

    void swap(gl_resource_handle& rhs) noexcept;

    GLuint get_handle() const;
    bool valid() const;

private:
    GLuint handle{0};
    releaser_func releaser;
};

//----------------------------------------------------------------------------//

class bindable {
public:
    class scoped final {
    public:
        scoped(const bindable& t);
        ~scoped() noexcept;

    private:
        const bindable& t;
    };

    bindable(GLuint handle, const gl_resource_handle::releaser_func& releaser);
    bindable(const gl_resource_handle::constructor_func& constructor,
             const gl_resource_handle::releaser_func& releaser);

    bindable(bindable&&) noexcept = default;
    bindable& operator=(bindable&&) noexcept = default;

    GLuint get_handle() const;

    void bind() const;
    void unbind() const;
    scoped get_scoped() const;

protected:
    ~bindable() noexcept = default;

private:
    virtual void do_bind(GLuint) const = 0;

    gl_resource_handle handle;
};

class usable {
public:
    class scoped final {
    public:
        scoped(const usable& t);
        ~scoped() noexcept;

    private:
        const usable& t;
    };

    usable(GLuint handle, const gl_resource_handle::releaser_func& releaser);
    usable(const gl_resource_handle::constructor_func& constructor,
           const gl_resource_handle::releaser_func& releaser);

    usable(usable&&) noexcept = default;
    usable& operator=(usable&&) noexcept = default;

    GLuint get_handle() const;

    void use() const;
    void unuse() const;
    scoped get_scoped() const;

protected:
    ~usable() noexcept = default;

private:
    virtual void do_use(GLuint) const = 0;

    gl_resource_handle handle;
};

}  // namespace mglu
