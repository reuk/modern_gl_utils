#pragma once

#include "drawable.h"
#include "quad_shader.h"

#define GLM_FORCE_RADIANS
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class ScreenQuad {
public:
    ScreenQuad(const QuadShader& shader) {
        std::vector<glm::vec3> vertices{
            {-1, -1, 0},
            {1, -1, 0},
            {-1, 1, 0},
            {-1, 1, 0},
            {1, -1, 0},
            {1, 1, 0},
        };
        vertex_bo.data(vertices);

        auto s_vao = vao.get_scoped();

        vertex_bo.bind();
        auto v_pos = shader.get_attrib_location("v_position");
        glEnableVertexAttribArray(v_pos);
        glVertexAttribPointer(v_pos, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    }

    void draw() const {
        auto s_vao = vao.get_scoped();
        glDrawArrays(GL_TRIANGLES, 0, 6);
    }

private:
    VAO vao;
    StaticVBO vertex_bo;
};
