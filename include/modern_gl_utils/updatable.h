#pragma once

namespace mglu {

class updatable {
public:
    updatable() = default;
    updatable(const updatable&) = default;
    updatable& operator=(const updatable&) = default;
    updatable(updatable&&) noexcept = default;
    updatable& operator=(updatable&&) noexcept = default;
    virtual ~updatable() noexcept = default;

    virtual void update(float dt) = 0;
};

}  // namespace mglu
