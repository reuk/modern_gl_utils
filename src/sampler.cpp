#include "modern_gl_utils/sampler.h"

namespace mglu {

Sampler::Sampler()
        : bindable([](auto& i) { glGenSamplers(1, &i); },
                   [](auto i) { glDeleteSamplers(1, &i); }) {
}

Sampler::Sampler(GLuint where)
        : Sampler() {
    set_where(where);
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
    glSamplerParameteri(get_handle(), a, b);
}

}  // namespace mglu
