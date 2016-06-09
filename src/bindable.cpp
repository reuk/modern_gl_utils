#include "modern_gl_utils/bindable.h"

IndexOwner::IndexOwner(GLuint index)
        : index(index) {
}

IndexOwner::IndexOwner(IndexOwner&& rhs) noexcept {
    std::swap(index, rhs.index);
}

IndexOwner& IndexOwner::operator=(IndexOwner&& rhs) noexcept {
    std::swap(index, rhs.index);
    return *this;
}

bool IndexOwner::valid() const {
    return index;
}

const GLuint &IndexOwner::get_index() const {
    return index;
}

GLuint& IndexOwner::get_index() {
    return index;
}

//----------------------------------------------------------------------------//

void Bindable::bind() {
    do_bind(get_index());
}

void Bindable::unbind() {
    do_bind(0);
}

//----------------------------------------------------------------------------//

void Usable::use() {
    do_use(get_index());
}

void Usable::unuse() {
    do_use(0);
}

//----------------------------------------------------------------------------//

Bindable::Scoped Bindable::get_scoped() {
    return Scoped(*this);
}

Usable::Scoped Usable::get_scoped() {
    return Scoped(*this);
}

Bindable::Scoped::Scoped(Bindable& t)
        : t(t) {
    t.bind();
}

Bindable::Scoped::~Scoped() noexcept {
    t.unbind();
}

Usable::Scoped::Scoped(Usable& t)
        : t(t) {
    t.use();
}

Usable::Scoped::~Scoped() noexcept {
    t.unuse();
}
