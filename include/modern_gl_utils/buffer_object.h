#pragma once

#include "bindable.h"

#include <vector>

namespace mglu {

template <GLuint type, GLuint mode>
class buffer_object final : public bindable {
public:
    buffer_object()
            : bindable([](auto& i) { glGenBuffers(1, &i); },
                       [](auto i) { glDeleteBuffers(1, &i); }) {
    }

    template <typename It>
    buffer_object(It begin, It end)
            : buffer_object() {
        data(begin, end);
    }

    template <typename T>
    buffer_object(const T& t)
            : buffer_object(std::begin(t), std::end(t)) {
    }

    buffer_object(buffer_object&&) noexcept = default;
    buffer_object& operator=(buffer_object&&) noexcept = default;

    void clear() {
        auto s = get_scoped(*this);
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

using static_vbo = buffer_object<GL_ARRAY_BUFFER, GL_STATIC_DRAW>;
using static_ibo = buffer_object<GL_ELEMENT_ARRAY_BUFFER, GL_STATIC_DRAW>;
using dynamic_vbo = buffer_object<GL_ARRAY_BUFFER, GL_DYNAMIC_DRAW>;
using dynamic_ibo = buffer_object<GL_ELEMENT_ARRAY_BUFFER, GL_DYNAMIC_DRAW>;

}  // namespace mglu
