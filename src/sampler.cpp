#include "modern_gl_utils/sampler.h"

Sampler::Sampler()
        : Bindable(0) {
    glGenSamplers(1, &get_index());
}

Sampler::~Sampler() {
    glDeleteSamplers(1, &get_index());
}

void Sampler::set_where(GLuint w) {
    where = w;
}

void Sampler::do_bind(GLuint ind) {
    glBindSampler(where, ind);
}

void Sampler::parameter_i(GLuint a, GLuint b) const {
    glSamplerParameteri(get_index(), a, b);
}
