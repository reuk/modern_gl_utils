#pragma once

#include "bindable.h"

#include <cassert>
#include <vector>

namespace mglu {

template <GLuint type, GLuint mode>
class buffer_object final : public bindable {
public:
    buffer_object()
            : bindable([](auto& i) { glGenBuffers(1, &i); },
                       [](auto i) { glDeleteBuffers(1, &i); }) {
    }

    template <typename T>
    buffer_object(const T* ptr, size_t items)
            : buffer_object() {
        data(ptr, items);
    }

    template <typename T>
    buffer_object(const T& t)
            : buffer_object(t.data(), t.size()) {
    }

    buffer_object(buffer_object&&) noexcept = default;
    buffer_object& operator=(buffer_object&&) noexcept = default;

    void clear() {
        const auto s = this->get_scoped();
        element_size = 0;
        num_elements = 0;
        glBufferData(type, num_elements, nullptr, mode);
    }

    template <typename T>
    void sub_data(size_t item_offset, const T* ptr, size_t items) {
        const auto in_buffer_bytes = sizeof(T) * items;
        const auto byte_offset = sizeof(T) * item_offset;

        assert(byte_offset + in_buffer_bytes <= size_in_bytes());

        const auto s = this->get_scoped();
        glBufferSubData(type, byte_offset, in_buffer_bytes, ptr);
    }

    template <typename T>
    void sub_data(size_t item_offset, const T& t) {
        sub_data(item_offset, t.data(), t.size());
    }

    template <typename T>
    void data(const T* ptr, size_t items) {
        if (items == num_elements) {
            sub_data(0, ptr, items);
        } else {
            element_size = sizeof(T);
            num_elements = items;

            const auto s = this->get_scoped();
            glBufferData(type, size_in_bytes(), ptr, mode);
        }
    }

    template <typename T>
    void data(const T& t) {
        data(t.data(), t.size());
    }

    size_t size() const {
        return num_elements;
    }

    size_t size_in_bytes() const {
        return element_size * num_elements;
    }

    size_t get_element_size() const {
        return element_size;
    }

private:
    void do_bind(GLuint index) const override {
        glBindBuffer(type, index);
    }

    size_t element_size{0};
    size_t num_elements{0};
};

using static_vbo = buffer_object<GL_ARRAY_BUFFER, GL_STATIC_DRAW>;
using static_ibo = buffer_object<GL_ELEMENT_ARRAY_BUFFER, GL_STATIC_DRAW>;
using dynamic_vbo = buffer_object<GL_ARRAY_BUFFER, GL_DYNAMIC_DRAW>;
using dynamic_ibo = buffer_object<GL_ELEMENT_ARRAY_BUFFER, GL_DYNAMIC_DRAW>;

}  // namespace mglu
