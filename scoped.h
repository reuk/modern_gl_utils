#pragma once

#include "bindable.h"

struct ScopedBind {
    ScopedBind(const Bindable& t)
        : t(t) {
        t.bind();
    }

    virtual ~ScopedBind() {
        t.unbind();
    }

private:
    const Bindable& t;
};

struct ScopedUse {
    ScopedUse(const Usable& t)
        : t(t) {
        t.use();
    }

    virtual ~ScopedUse() {
        t.unuse();
    }
private:
    const Usable& t;
};

inline auto scoped(const Bindable & t) {
    return ScopedBind(t);
}

inline auto scoped(const Usable & t) {
    return ScopedUse(t);
}
