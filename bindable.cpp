#include "bindable.h"

IndexOwner::IndexOwner(GLuint index)
    : index(index)
{

}

void Bindable::bind() const {
    do_bind(index);
}

void Bindable::unbind() const {
    do_bind(0);
}

void Usable::use() const {
    do_use(index);
}

void Usable::unuse() const {
    do_use(0);
}
