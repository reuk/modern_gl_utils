#pragma once

#include "glm/glm.hpp"

class Drawable {
public:
    Drawable() = default;
    Drawable(const Drawable&) = default;
    Drawable& operator=(const Drawable&) = default;
    Drawable(Drawable&&) noexcept = default;
    Drawable& operator=(Drawable&&) noexcept = default;
    virtual ~Drawable() noexcept = default;

    virtual void draw() const = 0;
};

class DrawableObject : public Drawable {
public:
    DrawableObject(DrawableObject* parent)
            : parent(parent) {}

    virtual glm::mat4 get_local_modelview_matrix() const = 0;
    glm::mat4 get_modelview_matrix() const;

private:
    DrawableObject* parent;
};
