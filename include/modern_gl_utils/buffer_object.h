#pragma once

#include "bindable.h"

#include <vector>

template <GLuint type, GLuint mode>
class BufferObject : public Bindable {
public:
    BufferObject()
            : Bindable(0) {
        glGenBuffers(1, &get_index());
    }

    ~BufferObject() {
        glDeleteBuffers(1, &get_index());
    }

    BufferObject(const BufferObject&) noexcept = default;
    BufferObject& operator=(const BufferObject&) noexcept = default;

    void do_bind(GLuint index) const override {
        glBindBuffer(type, index);
    }

    template <typename T>
    void data(const std::vector<T>& t) {
        auto s = get_scoped();
        auto in_size = t.size() * sizeof(T);
        if (in_size != size()) {
            elements = in_size;
            glBufferData(type, in_size, t.data(), mode);
        } else {
            glBufferSubData(type, 0, in_size, t.data());
        }
    }

    size_t size() const {
        return elements;
    }

private:
    size_t elements{0};
};

using StaticVBO = BufferObject<GL_ARRAY_BUFFER, GL_STATIC_DRAW>;
using StaticIBO = BufferObject<GL_ELEMENT_ARRAY_BUFFER, GL_STATIC_DRAW>;
using DynamicVBO = BufferObject<GL_ARRAY_BUFFER, GL_DYNAMIC_DRAW>;
using DynamicIBO = BufferObject<GL_ELEMENT_ARRAY_BUFFER, GL_DYNAMIC_DRAW>;
