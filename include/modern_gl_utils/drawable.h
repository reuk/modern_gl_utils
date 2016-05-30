#pragma once

class Drawable {
public:
    virtual ~Drawable() noexcept = default;
    virtual void draw() const = 0;
    virtual void lighting_pass() const {
    }
};
