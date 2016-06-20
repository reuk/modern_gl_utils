#pragma once

namespace mglu {

class Updatable {
public:
    Updatable() = default;
    Updatable(const Updatable&) = default;
    Updatable& operator=(const Updatable&) = default;
    Updatable(Updatable&&) noexcept = default;
    Updatable& operator=(Updatable&&) noexcept = default;
    virtual ~Updatable() noexcept = default;

    virtual void update(float dt) = 0;
};

}  // namespace mglu
