#pragma once

#include "bindable.h"

#include <vector>

namespace mglu {

template <GLuint type, GLuint mode>
class BufferObject : public Bindable {
public:
    BufferObject()
            : Bindable(0) {
        glGenBuffers(1, &get_index());
    }

    template <typename It>
    BufferObject(It begin, It end)
            : BufferObject() {
        data(begin, end);
    }

    virtual ~BufferObject() noexcept {
        glDeleteBuffers(1, &get_index());
    }

    BufferObject(BufferObject&&) noexcept = default;
    BufferObject& operator=(BufferObject&&) noexcept = default;

    void do_bind(GLuint index) const override {
        glBindBuffer(type, index);
    }

    void clear() {
        auto s = get_scoped();
        elements = 0;
        glBufferData(type, elements, nullptr, mode);
    }

    template <typename It>
    void data(It begin, It end) {
        auto s = get_scoped();
        auto in_element = sizeof(*begin);
        auto in_elements = std::distance(begin, end);
        auto in_buffer_size = in_element * in_elements;
        if (in_buffer_size != buffer_size()) {
            element = in_element;
            elements = in_elements;
            glBufferData(type, buffer_size(), begin, mode);
        } else {
            glBufferSubData(type, 0, buffer_size(), begin);
        }
    }

    size_t size() const {
        return elements;
    }

    size_t element_size() const {
        return element;
    }

    size_t buffer_size() const {
        return size() * element_size();
    }

private:
    size_t element{0};
    size_t elements{0};
};

using StaticVBO = BufferObject<GL_ARRAY_BUFFER, GL_STATIC_DRAW>;
using StaticIBO = BufferObject<GL_ELEMENT_ARRAY_BUFFER, GL_STATIC_DRAW>;
using DynamicVBO = BufferObject<GL_ARRAY_BUFFER, GL_DYNAMIC_DRAW>;
using DynamicIBO = BufferObject<GL_ELEMENT_ARRAY_BUFFER, GL_DYNAMIC_DRAW>;

}  // namespace mglu
