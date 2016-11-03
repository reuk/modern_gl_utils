#pragma once

#include "exceptions.h"

#include <OpenGL/gl3.h>
#include <string>
#include <vector>

namespace mglu {

//----------------------------------------------------------------------------//

namespace exceptions {

class check_failed final : public exception {
public:
    using exception::exception;
};

}  // namespace exceptions

//----------------------------------------------------------------------------//

namespace checking {

namespace detail {

template <GLenum>
struct get_shader_iv_trait;
template <>
struct get_shader_iv_trait<GL_SHADER_TYPE> final {
    using return_type = GLint;
};
template <>
struct get_shader_iv_trait<GL_DELETE_STATUS> final {
    using return_type = bool;
};
template <>
struct get_shader_iv_trait<GL_COMPILE_STATUS> final {
    static constexpr const char* description{"compile status"};
    using return_type = bool;
};
template <>
struct get_shader_iv_trait<GL_INFO_LOG_LENGTH> final {
    using return_type = GLint;
};
template <>
struct get_shader_iv_trait<GL_SHADER_SOURCE_LENGTH> final {
    using return_type = GLint;
};

template <GLenum flag>
constexpr const char* get_shader_iv_description_v =
    get_shader_iv_trait<flag>::description;

template <GLenum flag>
using get_shader_iv_trait_t = typename get_shader_iv_trait<flag>::return_type;

template <GLenum>
struct get_program_iv_trait;
template <>
struct get_program_iv_trait<GL_DELETE_STATUS> final {
    using return_type = bool;
};
template <>
struct get_program_iv_trait<GL_LINK_STATUS> final {
    static constexpr const char* description{"link status"};
    using return_type = bool;
};
template <>
struct get_program_iv_trait<GL_VALIDATE_STATUS> final {
    static constexpr const char* description{"validate status"};
    using return_type = bool;
};
template <>
struct get_program_iv_trait<GL_INFO_LOG_LENGTH> final {
    using return_type = GLint;
};
template <>
struct get_program_iv_trait<GL_ATTACHED_SHADERS> final {
    using return_type = GLint;
};
template <>
struct get_program_iv_trait<GL_ACTIVE_ATTRIBUTES> final {
    using return_type = GLint;
};
template <>
struct get_program_iv_trait<GL_ACTIVE_ATTRIBUTE_MAX_LENGTH> final {
    using return_type = GLint;
};
template <>
struct get_program_iv_trait<GL_ACTIVE_UNIFORMS> final {
    using return_type = GLint;
};
template <>
struct get_program_iv_trait<GL_ACTIVE_UNIFORM_MAX_LENGTH> final {
    using return_type = GLint;
};

template <GLenum flag>
constexpr const char* get_program_iv_description_v =
    get_program_iv_trait<flag>::description;

template <GLenum flag>
using get_program_iv_trait_t = typename get_program_iv_trait<flag>::return_type;

template <typename T>
T convert(GLint);
template <>
inline bool convert(GLint i) {
    return i == GL_TRUE;
}
template <>
inline GLint convert(GLint i) {
    return i;
}

}  // namespace detail

template <typename T>
inline std::string get_info_log(T func, GLuint handle) {
    std::vector<char> log(1 << 10);
    GLsizei length{0};
    func(handle, log.size(), &length, log.data());
    return std::string(log.begin(), log.begin() + length);
}

inline std::string get_shader_info_log(GLuint handle) {
    return get_info_log(glGetShaderInfoLog, handle);
}

inline std::string get_program_info_log(GLuint handle) {
    return get_info_log(glGetProgramInfoLog, handle);
}

template <GLenum flag>
inline detail::get_shader_iv_trait_t<flag> get_shader_iv(GLuint handle) {
    GLint ret;
    glGetShaderiv(handle, flag, &ret);
    return detail::convert<detail::get_shader_iv_trait_t<flag>>(ret);
}

template <GLenum flag>
inline detail::get_program_iv_trait_t<flag> get_program_iv(GLuint handle) {
    GLint ret;
    glGetProgramiv(handle, flag, &ret);
    return detail::convert<detail::get_program_iv_trait_t<flag>>(ret);
}

template <GLenum flag>
inline void shader_iv_throw_if_false(GLuint handle) {
    if (!get_shader_iv<flag>(handle)) {
        const auto msg =
            std::string(detail::get_shader_iv_description_v<flag>) + ": " +
            get_shader_info_log(handle);
        throw exceptions::check_failed(msg);
    }
}

template <GLenum flag>
inline void program_iv_throw_if_false(GLuint handle) {
    if (!get_program_iv<flag>(handle)) {
        const auto msg =
            std::string(detail::get_program_iv_description_v<flag>) + ": " +
            get_program_info_log(handle);
        throw exceptions::check_failed(msg);
    }
}

}  // namespace checking

//----------------------------------------------------------------------------//

}  // namespace mglu
