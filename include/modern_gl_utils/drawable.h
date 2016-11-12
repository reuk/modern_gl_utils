#pragma once

#include "glm/fwd.hpp"

namespace mglu {

class drawable {
public:
    drawable() = default;
    drawable(const drawable&) = default;
    drawable& operator=(const drawable&) = default;
    drawable(drawable&&) noexcept = default;
    drawable& operator=(drawable&&) noexcept = default;
    virtual ~drawable() noexcept = default;

    void draw(const glm::mat4& model_matrix) const;

private:
    virtual void do_draw(const glm::mat4& model_matrix) const = 0;
    virtual glm::mat4 get_local_model_matrix() const = 0;
};

}  // namespace mglu
