#pragma once

#include "drawable.h"
#include "scoped.h"
#include "vao.h"
#include "buffer_object.h"
#include "generic_shader.h"

#include <glm/glm.hpp>

#include <vector>

template <GLuint mode>
class StaticDrawable : public Drawable {
public:
    StaticDrawable(GenericShader &shader_program,
                   const std::vector<GLfloat> &g,
                   const std::vector<GLfloat> &c,
                   const std::vector<GLushort> &i)
            : shader_program(shader_program)
            , size(i.size()) {
        geometry.data(g);
        colors.data(c);
        ibo.data(i);

        configure_vao();
    }

    StaticDrawable(const StaticDrawable &rhs) noexcept = delete;
    StaticDrawable &operator=(const StaticDrawable &rhs) noexcept = delete;
    StaticDrawable(StaticDrawable &&rhs) noexcept
        : shader_program(rhs.shader_program),
          geometry(std::move(rhs.geometry)),
          colors(std::move(rhs.colors)),
          ibo(std::move(rhs.ibo)),
          size(rhs.size) {
        configure_vao();
    }

    StaticDrawable &operator=(StaticDrawable &&rhs) noexcept {
        shader_program = std::move(rhs.shader_program);
        geometry = std::move(rhs.geometry);
        colors = std::move(rhs.colors);
        ibo = std::move(rhs.ibo);
        size = rhs.size;

        configure_vao();

        return *this;
    }

    virtual ~StaticDrawable() noexcept = default;

    void set_model_matrix(const glm::mat4 &model_matrix) const {
        shader_program.set_model_matrix(model_matrix);
    }

    void draw() const override {
        ScopedBind<VAO> scoped(vao);
        glDrawElements(mode, size, GL_UNSIGNED_SHORT, nullptr);
    }

    GenericShader &shader_program;

private:
    void configure_vao() const {
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

    VAO vao;
    StaticVBO geometry;
    StaticVBO colors;
    StaticIBO ibo;

    int size;
};
