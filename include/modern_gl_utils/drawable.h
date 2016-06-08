#pragma once

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
