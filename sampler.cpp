#include "sampler.h"

using namespace std;

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

void Sampler::bind(GLuint where) const {
    glBindSampler(where, get_index());
}

void Sampler::parameter_i(GLuint a, GLuint b) const {
    glSamplerParameteri(get_index(), a, b);
}
