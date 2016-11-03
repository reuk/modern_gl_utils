#include "modern_gl_utils/exceptions.h"

namespace mglu {

namespace exceptions {

void do_throw(GLenum e) {
    switch (e) {
        case GL_INVALID_ENUM:
            throw detail::construct_exception<GL_INVALID_ENUM>();
        case GL_INVALID_VALUE:
            throw detail::construct_exception<GL_INVALID_VALUE>();
        case GL_INVALID_OPERATION:
            throw detail::construct_exception<GL_INVALID_OPERATION>();
        case GL_INVALID_FRAMEBUFFER_OPERATION:
            throw detail::construct_exception<
                GL_INVALID_FRAMEBUFFER_OPERATION>();
        case GL_OUT_OF_MEMORY:
            throw detail::construct_exception<GL_OUT_OF_MEMORY>();
        default:
            throw unknown(to_string(e));
    }
}

void throw_if_error(GLenum e) {
    if (e != GL_NO_ERROR) {
        do_throw(e);
    }
}

}  // namespace exceptions

void check_for_gl_error() {
#ifndef NDEBUG
    exceptions::throw_if_error(glGetError());
#endif
}

void clear_gl_errors() {
    while (glGetError() != GL_NO_ERROR) {
    }
}

}  // namespace mglu

