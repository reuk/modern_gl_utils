#include "modern_gl_utils/bindable.h"
#include "modern_gl_utils/exceptions.h"

#include <stdexcept>

namespace mglu {

gl_resource_handle::gl_resource_handle(GLuint handle,
                                       const releaser_func& releaser)
        : handle(handle)
        , releaser(releaser) {
    if (!handle) {
        throw std::runtime_error("handle is null!");
    }
}

gl_resource_handle::gl_resource_handle(const constructor_func& constructor,
                                       const releaser_func& releaser)
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

bindable::bindable(GLuint handle,
                   const gl_resource_handle::releaser_func& releaser)
        : handle(handle, releaser) {
    check_for_gl_error();
}

bindable::bindable(const gl_resource_handle::constructor_func& constructor,
                   const gl_resource_handle::releaser_func& releaser)
        : handle(constructor, releaser) {
    check_for_gl_error();
}

GLuint bindable::get_handle() const {
    return handle.get_handle();
}

bindable::scoped::scoped(const bindable& t)
        : t(t) {
    t.bind();
}
bindable::scoped::~scoped() noexcept {
    t.unbind();
}

void bindable::bind() const {
    do_bind(handle.get_handle());
    check_for_gl_error();
}
void bindable::unbind() const {
    do_bind(0);
}
bindable::scoped bindable::get_scoped() const {
    return scoped(*this);
}

//----------------------------------------------------------------------------//

usable::usable(GLuint handle, const gl_resource_handle::releaser_func& releaser)
        : handle(handle, releaser) {
    check_for_gl_error();
}

usable::usable(const gl_resource_handle::constructor_func& constructor,
               const gl_resource_handle::releaser_func& releaser)
        : handle(constructor, releaser) {
    check_for_gl_error();
}

GLuint usable::get_handle() const {
    return handle.get_handle();
}

usable::scoped::scoped(const usable& t)
        : t(t) {
    t.use();
}
usable::scoped::~scoped() noexcept {
    t.unuse();
}

void usable::use() const {
    do_use(handle.get_handle());
}
void usable::unuse() const {
    do_use(0);
}
usable::scoped usable::get_scoped() const {
    return scoped(*this);
}

}  // namespace mglu
