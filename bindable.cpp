#include "bindable.h"

IndexOwner::IndexOwner(GLuint index)
        : index(std::make_unique<GLuint>(index)) {
}

bool IndexOwner::valid() const {
    return index != nullptr;
}

GLuint IndexOwner::get_index() const {
    return valid() ? *index : 0;
}
GLuint& IndexOwner::get_index() {
    return *index;
}

void Bindable::bind() const {
    do_bind(get_index());
}

void Bindable::unbind() const {
    do_bind(0);
}

void Usable::use() const {
    do_use(get_index());
}

void Usable::unuse() const {
    do_use(0);
}

Bindable::Scoped Bindable::get_scoped() const {
    return Scoped(*this);
}

Usable::Scoped Usable::get_scoped() const {
    return Scoped(*this);
}

Bindable::Scoped::Scoped(const Bindable& t)
        : t(t) {
    t.bind();
}

Bindable::Scoped::~Scoped() noexcept {
    t.unbind();
}

Usable::Scoped::Scoped(const Usable& t)
        : t(t) {
    t.use();
}

Usable::Scoped::~Scoped() noexcept {
    t.unuse();
}
