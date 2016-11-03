#pragma once

#include "bindable.h"
#include "buffer_object.h"
#include "exceptions.h"

#include <OpenGL/gl3.h>

namespace mglu {

class vao final : public bindable {
public:
    vao();

    void enable_vertex_attrib_array(GLuint) const;
    void disable_vertex_attrib_array(GLuint) const;

    void vertex_attrib_pointer(GLuint pos, GLint size, GLenum type) const;

private:
    void do_bind(GLuint) const override;
};

template <GLuint type, GLuint mode>
inline void enable_and_bind_buffer(const vao& vao,
                                   const buffer_object<type, mode>& buffer,
                                   GLuint pos,
                                   GLint size,
                                   GLenum t) {
    vao.enable_vertex_attrib_array(pos);
    buffer.bind();
    vao.vertex_attrib_pointer(pos, size, t);
}

}  // namespace mglu
