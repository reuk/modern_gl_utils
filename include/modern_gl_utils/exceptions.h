#pragma once

#include <OpenGL/gl3.h>
#include <stdexcept>

namespace mglu {

namespace exceptions {

class exception : public std::runtime_error {
public:
    using std::runtime_error::runtime_error;

protected:
    ~exception() noexcept = default;
};

class invalid_enum final : public exception {
    using exception::exception;
};
class invalid_value final : public exception {
    using exception::exception;
};
class invalid_operation final : public exception {
    using exception::exception;
};
class invalid_framebuffer_operation final : public exception {
    using exception::exception;
};
class out_of_memory final : public exception {
    using exception::exception;
};

class unknown final : public exception {
    using exception::exception;
};

namespace detail {

template <GLenum>
struct gl_error_type_trait final {
    static constexpr const char* description{"unknown error"};
    using exception = unknown;
};

template <>
struct gl_error_type_trait<GL_NO_ERROR> final {
    static constexpr const char* description{"no error"};
};

template <>
struct gl_error_type_trait<GL_INVALID_ENUM> final {
    static constexpr const char* description{"invalid enum"};
    using exception = invalid_enum;
};
template <>
struct gl_error_type_trait<GL_INVALID_VALUE> final {
    static constexpr const char* description{"invalid value"};
    using exception = invalid_value;
};
template <>
struct gl_error_type_trait<GL_INVALID_OPERATION> final {
    static constexpr const char* description{"invalid operation"};
    using exception = invalid_operation;
};
template <>
struct gl_error_type_trait<GL_INVALID_FRAMEBUFFER_OPERATION> final {
    static constexpr const char* description{"invalid framebuffer operation"};
    using exception = invalid_framebuffer_operation;
};
template <>
struct gl_error_type_trait<GL_OUT_OF_MEMORY> final {
    static constexpr const char* description{"out of memory"};
    using exception = out_of_memory;
};

template <GLenum flag>
constexpr const char* gl_error_type_description_v =
    gl_error_type_trait<flag>::description;
template <GLenum flag>
using gl_error_type_exception_t = typename gl_error_type_trait<flag>::exception;

template <GLenum flag>
gl_error_type_exception_t<flag> construct_exception() {
    return gl_error_type_exception_t<flag>(gl_error_type_description_v<flag>);
}

}  // namespace detail

constexpr const char* to_string(GLenum e) {
    switch (e) {
        case GL_NO_ERROR:
            return detail::gl_error_type_description_v<GL_NO_ERROR>;
        case GL_INVALID_ENUM:
            return detail::gl_error_type_description_v<GL_INVALID_ENUM>;
        case GL_INVALID_VALUE:
            return detail::gl_error_type_description_v<GL_INVALID_VALUE>;
        case GL_INVALID_OPERATION:
            return detail::gl_error_type_description_v<GL_INVALID_OPERATION>;
        case GL_INVALID_FRAMEBUFFER_OPERATION:
            return detail::gl_error_type_description_v<
                GL_INVALID_FRAMEBUFFER_OPERATION>;
        case GL_OUT_OF_MEMORY:
            return detail::gl_error_type_description_v<GL_OUT_OF_MEMORY>;
        default:
            return "unknown enum value";
    }
}

void do_throw(GLenum e);
void throw_if_error(GLenum e);

}  // namespace exceptions

void check_for_gl_error();
void clear_gl_errors();

}  // namespace mglu
