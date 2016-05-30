#pragma once

class Updatable {
public:
    virtual ~Updatable() noexcept = default;
    virtual void update(float dt) = 0;
};
