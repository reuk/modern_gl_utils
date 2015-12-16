#include "sampler.h"

using namespace std;

Sampler::Sampler()
        : Bindable(0) {
    glGenSamplers(1, &index);
}

Sampler::~Sampler() {
    glDeleteSamplers(1, &index);
}

void Sampler::set_where(GLuint w) {
    where = w;
}

void Sampler::bind(GLuint where) const {
    glBindSampler(where, index);
}

void Sampler::parameter_i(GLuint a, GLuint b) const {
    glSamplerParameteri(index, a, b);
}
