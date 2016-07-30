#include "modern_gl_utils/bindable.h"

namespace mglu {

gl_resource_handle::gl_resource_handle(GLuint handle,
                                       const releaser_func& releaser)
        : handle(handle)
        , releaser(releaser) {
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
    releaser(handle);
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
    return handle;
}

bool gl_resource_handle::valid() const {
    return handle;
}

//----------------------------------------------------------------------------//

bindable::scoped::scoped(const bindable& t)
        : t(t) {
    t.bind();
}
bindable::scoped::~scoped() noexcept {
    t.unbind();
}

void bindable::bind() const {
    do_bind(get_handle());
}
void bindable::unbind() const {
    do_bind(0);
}

//----------------------------------------------------------------------------//

usable::scoped::scoped(const usable& t)
        : t(t) {
    t.use();
}
usable::scoped::~scoped() noexcept {
    t.unuse();
}

void usable::use() const {
    do_use(get_handle());
}
void usable::unuse() const {
    do_use(0);
}

//----------------------------------------------------------------------------//

bindable::scoped get_scoped(const bindable& u) {
    return bindable::scoped(u);
}

usable::scoped get_scoped(const usable& u) {
    return usable::scoped(u);
}

}  // namespace mglu
