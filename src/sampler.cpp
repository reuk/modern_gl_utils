#include "modern_gl_utils/sampler.h"

namespace mglu {

Sampler::Sampler()
        : Bindable(0) {
    glGenSamplers(1, &get_index());
}

Sampler::Sampler(GLuint where)
        : Sampler() {
    set_where(where);
}

Sampler::~Sampler() {
    glDeleteSamplers(1, &get_index());
}

void Sampler::set_where(GLuint w) {
    where = w;
}

GLuint Sampler::get_where() const {
    return where;
}

void Sampler::do_bind(GLuint ind) const {
    glBindSampler(where, ind);
}

void Sampler::parameter_i(GLuint a, GLuint b) const {
    glSamplerParameteri(get_index(), a, b);
}

}  // namespace mglu