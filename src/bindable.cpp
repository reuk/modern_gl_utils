#include "modern_gl_utils/bindable.h"
#include "modern_gl_utils/exceptions.h"

#include <stdexcept>

namespace mglu {

gl_resource_handle::gl_resource_handle(GLuint handle, releaser_func releaser)
        : handle(handle)
        , releaser(releaser) {
    if (!handle) {
        throw std::runtime_error("handle is null!");
    }
}

gl_resource_handle::gl_resource_handle(constructor_func constructor,
                                       releaser_func releaser)
        : gl_resource_handle(
              [&constructor] {
                  GLuint i;
                  constructor(i);
                  return i;
              }(),
              releaser) {
}

gl_resource_handle::~gl_resource_handle() noexcept {
    if (releaser) {
        releaser(handle);
    }
}

gl_resource_handle::gl_resource_handle(gl_resource_handle&& rhs) noexcept {
    swap(rhs);
}

gl_resource_handle& gl_resource_handle::operator=(
    gl_resource_handle&& rhs) noexcept {
    swap(rhs);
    return *this;
}

void gl_resource_handle::swap(gl_resource_handle& rhs) noexcept {
    using std::swap;
    swap(handle, rhs.handle);
    swap(releaser, rhs.releaser);
}

GLuint gl_resource_handle::get_handle() const {
    if (!valid()) {
        throw std::runtime_error("tried to use an invalid resource handle");
    }
    return handle;
}

bool gl_resource_handle::valid() const {
    return handle;
}

//----------------------------------------------------------------------------//

scoped_from_this::scoped scoped_from_this::get_scoped() const {
    return scoped(*this);
}

scoped_from_this::scoped::scoped(const scoped_from_this& t)
        : t(t) {
    t.on_scope_begin();
}
scoped_from_this::scoped::~scoped() noexcept {
    t.on_scope_end();
}

//----------------------------------------------------------------------------//

bindable::bindable(GLuint handle, gl_resource_handle::releaser_func releaser)
        : handle(handle, releaser) {
    check_for_gl_error();
}
bindable::bindable(gl_resource_handle::constructor_func constructor,
                   gl_resource_handle::releaser_func releaser)
        : handle(constructor, releaser) {
    check_for_gl_error();
}

GLuint bindable::get_handle() const {
    return handle.get_handle();
}

void bindable::bind() const {
    do_bind(handle.get_handle());
}
void bindable::unbind() const {
    do_bind(0);
}

void bindable::on_scope_begin() const {
    bind();
}
void bindable::on_scope_end() const {
    unbind();
}

//----------------------------------------------------------------------------//

usable::usable(GLuint handle, gl_resource_handle::releaser_func releaser)
        : handle(handle, releaser) {
    check_for_gl_error();
}
usable::usable(gl_resource_handle::constructor_func constructor,
               gl_resource_handle::releaser_func releaser)
        : handle(constructor, releaser) {
    check_for_gl_error();
}

GLuint usable::get_handle() const {
    return handle.get_handle();
}

void usable::use() const {
    do_use(handle.get_handle());
}
void usable::unuse() const {
    do_use(0);
}

void usable::on_scope_begin() const {
    use();
}

void usable::on_scope_end() const {
    unuse();
}

}  // namespace mglu