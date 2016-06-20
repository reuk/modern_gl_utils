#pragma once

#include "buffer_object.h"
#include "drawable.h"
#include "generic_shader.h"
#include "scoped.h"
#include "vao.h"

#include "glm/glm.hpp"

#include <vector>

namespace mglu {

template <GLuint mode>
class StaticDrawable : public Drawable {
public:
    StaticDrawable(GenericShader &shader_program,
                   const std::vector<GLfloat> &g,
                   const std::vector<GLfloat> &c,
                   const std::vector<GLushort> &i)
            : shader_program(shader_program)
            , geometry(g)
            , colors(c)
            , ibo(i) {
        ScopedBind<VAO> scoped(vao);

        auto v_position = shader_program.get_attrib_location("v_position");
        glEnableVertexAttribArray(v_position);
        geometry.bind();
        glVertexAttribPointer(v_position, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

        auto v_color = shader_program.get_attrib_location("v_color");
        glEnableVertexAttribArray(v_color);
        colors.bind();
        glVertexAttribPointer(v_color, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

        ibo.bind();
    }

    StaticDrawable(const StaticDrawable &rhs) noexcept = delete;
    StaticDrawable &operator=(const StaticDrawable &rhs) noexcept = delete;
    StaticDrawable(StaticDrawable &&rhs) noexcept = default;
    StaticDrawable &operator=(StaticDrawable &&rhs) noexcept = default;

    void set_model_matrix(const glm::mat4 &model_matrix) const {
        shader_program.set_model_matrix(model_matrix);
    }

    void draw() const override {
        auto s = vao.get_scoped();
        glDrawElements(mode, ibo.size(), GL_UNSIGNED_SHORT, nullptr);
    }

    GenericShader &shader_program;

private:
    VAO vao;
    StaticVBO geometry;
    StaticVBO colors;
    StaticIBO ibo;
};

}  // namespace mglu
