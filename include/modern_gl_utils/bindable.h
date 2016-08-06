#pragma once

#include "modern_gl_utils/exceptions.h"

#include <functional>
#include <memory>

namespace mglu {

class gl_resource_handle final {
public:
    using constructor_func = std::function<void(GLuint&)>;
    using releaser_func = std::function<void(GLuint)>;

    gl_resource_handle(GLuint handle, releaser_func releaser);
    gl_resource_handle(constructor_func constructor, releaser_func releaser);

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

class scoped_from_this {
    class scoped;

public:
    scoped get_scoped() const;

protected:
    ~scoped_from_this() noexcept = default;

private:
    class scoped final {
    public:
        scoped(const scoped_from_this& t);
        ~scoped() noexcept;

    private:
        const scoped_from_this& t;
    };

    virtual void on_scope_begin() const = 0;
    virtual void on_scope_end() const = 0;
};

//----------------------------------------------------------------------------//

class bindable : public scoped_from_this {
public:
    bindable(GLuint handle, gl_resource_handle::releaser_func releaser);
    bindable(gl_resource_handle::constructor_func constructor,
             gl_resource_handle::releaser_func releaser);

    bindable(bindable&&) noexcept = default;
    bindable& operator=(bindable&&) noexcept = default;

    GLuint get_handle() const;

    void bind() const;
    void unbind() const;

protected:
    ~bindable() noexcept = default;

private:
    virtual void do_bind(GLuint) const = 0;

    void on_scope_begin() const override;
    void on_scope_end() const override;

    gl_resource_handle handle;
};

//----------------------------------------------------------------------------//

class usable : public scoped_from_this {
public:
    usable(GLuint handle, gl_resource_handle::releaser_func releaser);
    usable(gl_resource_handle::constructor_func constructor,
           gl_resource_handle::releaser_func releaser);

    usable(usable&&) noexcept = default;
    usable& operator=(usable&&) noexcept = default;

    GLuint get_handle() const;

    void use() const;
    void unuse() const;

protected:
    ~usable() noexcept = default;

private:
    virtual void do_use(GLuint) const = 0;

    void on_scope_begin() const override;
    void on_scope_end() const override;

    gl_resource_handle handle;
};

}  // namespace mglu
