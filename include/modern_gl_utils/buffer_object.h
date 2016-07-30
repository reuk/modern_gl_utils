#pragma once

#include "bindable.h"

#include <vector>

namespace mglu {

template <GLuint type, GLuint mode>
class BufferObject final : public bindable {
public:
    BufferObject()
            : bindable([](auto& i) { glGenBuffers(1, &i); },
                       [](auto i) { glDeleteBuffers(1, &i); }) {
    }

    template <typename It>
    BufferObject(It begin, It end)
            : BufferObject() {
        data(begin, end);
    }

    template <typename T>
    BufferObject(const T& t)
            : BufferObject(std::begin(t), std::end(t)) {
    }

    BufferObject(BufferObject&&) noexcept = default;
    BufferObject& operator=(BufferObject&&) noexcept = default;

    void clear() {
        auto s = get_scoped(*this);
        elements = 0;
        glBufferData(type, elements, nullptr, mode);
    }

    template <typename It>
    void data(It begin, It end) {
        auto s = get_scoped(*this);
        auto in_element = sizeof(*begin);
        auto in_elements = std::distance(begin, end);
        auto in_buffer_size = in_element * in_elements;
        if (in_buffer_size != buffer_size()) {
            element = in_element;
            elements = in_elements;
            glBufferData(type, buffer_size(), &(*begin), mode);
        } else {
            glBufferSubData(type, 0, buffer_size(), &(*begin));
        }
    }

    template <typename T>
    void data(const T& t) {
        data(std::begin(t), std::end(t));
    }

    size_t size() const {
        return elements;
    }

    size_t element_size() const {
        return element;
    }

    size_t buffer_size() const {
        return element * elements;
    }

private:
    void do_bind(GLuint index) const override {
        glBindBuffer(type, index);
    }

    size_t element{0};
    size_t elements{0};
};

using StaticVBO = BufferObject<GL_ARRAY_BUFFER, GL_STATIC_DRAW>;
using StaticIBO = BufferObject<GL_ELEMENT_ARRAY_BUFFER, GL_STATIC_DRAW>;
using DynamicVBO = BufferObject<GL_ARRAY_BUFFER, GL_DYNAMIC_DRAW>;
using DynamicIBO = BufferObject<GL_ELEMENT_ARRAY_BUFFER, GL_DYNAMIC_DRAW>;

}  // namespace mglu
