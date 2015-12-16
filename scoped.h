#pragma once

template <typename T>
struct ScopedBind {
    ScopedBind(const T& t) {
        t.bind();
    }

    virtual ~ScopedBind() {
        T::unbind();
    }
};

template <typename T>
struct ScopedUse {
    ScopedUse(const T& t) {
        t.use();
    }

    virtual ~ScopedUse() {
        T::unuse();
    }
};

template <typename T>
auto bind_scoped(const T& t) {
    return ScopedBind<T>(t);
}

template <typename T>
auto use_scoped(const T& t) {
    return ScopedUse<T>(t);
}
