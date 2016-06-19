#pragma once

#include "glm/fwd.hpp"

namespace mglu {

class Drawable {
public:
    Drawable() = default;
    Drawable(const Drawable&) = default;
    Drawable& operator=(const Drawable&) = default;
    Drawable(Drawable&&) noexcept = default;
    Drawable& operator=(Drawable&&) noexcept = default;
    virtual ~Drawable() noexcept = default;

    void draw(const glm::mat4& modelview_matrix) const;

private:
    virtual void do_draw(const glm::mat4& modelview_matrix) const = 0;
    virtual glm::mat4 get_local_modelview_matrix() const = 0;
};

}  // namespace mglu
