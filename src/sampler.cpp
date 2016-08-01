#include "modern_gl_utils/sampler.h"

namespace mglu {

sampler::sampler()
        : bindable([](auto& i) { glGenSamplers(1, &i); },
                   [](auto i) { glDeleteSamplers(1, &i); }) {
}

sampler::sampler(GLuint where)
        : sampler() {
    set_where(where);
}

void sampler::set_where(GLuint w) {
    where = w;
}

GLuint sampler::get_where() const {
    return where;
}

void sampler::do_bind(GLuint ind) const {
    glBindSampler(where, ind);
}

void sampler::parameter_i(GLuint a, GLuint b) const {
    glSamplerParameteri(get_handle(), a, b);
}

}  // namespace mglu
