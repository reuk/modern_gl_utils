#pragma once

#include "program.h"

#include "glm/glm.hpp"

namespace mglu {

class generic_shader final {
public:
    generic_shader();

    auto get_attrib_location_v_position() const {
        return program.get_attrib_location("v_position");
    }

    auto get_attrib_location_v_color() const {
        return program.get_attrib_location("v_color");
    }

    void set_model_matrix(const glm::mat4 &mat) const;
    void set_view_matrix(const glm::mat4 &mat) const;
    void set_projection_matrix(const glm::mat4 &mat) const;

    auto get_scoped() const {
        return program.get_scoped();
    }

private:
    static const char *vertex_shader;
    static const char *fragment_shader;

    program program;
};

}  // namespace mglu
