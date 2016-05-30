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

    BufferObject(BufferObject&&) noexcept = default;
    BufferObject& operator=(BufferObject&&) noexcept = default;
    BufferObject(const BufferObject&) noexcept = default;
    BufferObject& operator=(const BufferObject&) noexcept = default;

    /*
    BufferObject(const BufferObject &rhs) noexcept : Bindable(0) {
        glGenBuffers(1, &index);

        auto size = 0;

        glBindBuffer(GL_COPY_READ_BUFFER, rhs.index);
        glGetBufferParameteriv(GL_COPY_READ_BUFFER, GL_BUFFER_SIZE, &size);

        glBindBuffer(GL_COPY_WRITE_BUFFER, index);
        glBufferData(GL_COPY_WRITE_BUFFER, size, nullptr, mode);

        glCopyBufferSubData(
            GL_COPY_READ_BUFFER, GL_COPY_WRITE_BUFFER, 0, 0, size);

        glBindBuffer(GL_COPY_READ_BUFFER, 0);
        glBindBuffer(GL_COPY_WRITE_BUFFER, 0);
    }

    BufferObject &operator=(const BufferObject &rhs) noexcept {
        index = 0;

        glGenBuffers(1, &index);

        auto size = 0;

        glBindBuffer(GL_COPY_READ_BUFFER, rhs.index);
        glGetBufferParameteriv(GL_COPY_READ_BUFFER, GL_BUFFER_SIZE, &size);

        glBindBuffer(GL_COPY_WRITE_BUFFER, index);
        glBufferData(GL_COPY_WRITE_BUFFER, size, nullptr, mode);

        glCopyBufferSubData(
            GL_COPY_READ_BUFFER, GL_COPY_WRITE_BUFFER, 0, 0, size);

        glBindBuffer(GL_COPY_READ_BUFFER, 0);
        glBindBuffer(GL_COPY_WRITE_BUFFER, 0);

        return *this;
    }

    BufferObject(BufferObject &&rhs) noexcept : Bindable(0) {
        glGenBuffers(1, &index);

        auto size = 0;

        glBindBuffer(GL_COPY_READ_BUFFER, rhs.index);
        glGetBufferParameteriv(GL_COPY_READ_BUFFER, GL_BUFFER_SIZE, &size);

        glBindBuffer(GL_COPY_WRITE_BUFFER, index);
        glBufferData(GL_COPY_WRITE_BUFFER, size, nullptr, mode);

        glCopyBufferSubData(
            GL_COPY_READ_BUFFER, GL_COPY_WRITE_BUFFER, 0, 0, size);

        glBindBuffer(GL_COPY_READ_BUFFER, 0);
        glBindBuffer(GL_COPY_WRITE_BUFFER, 0);
    }

    BufferObject &operator=(BufferObject &&rhs) noexcept {
        index = 0;

        glGenBuffers(1, &index);

        auto size = 0;

        glBindBuffer(GL_COPY_READ_BUFFER, rhs.index);
        glGetBufferParameteriv(GL_COPY_READ_BUFFER, GL_BUFFER_SIZE, &size);

        glBindBuffer(GL_COPY_WRITE_BUFFER, index);
        glBufferData(GL_COPY_WRITE_BUFFER, size, nullptr, mode);

        glCopyBufferSubData(
            GL_COPY_READ_BUFFER, GL_COPY_WRITE_BUFFER, 0, 0, size);

        glBindBuffer(GL_COPY_READ_BUFFER, 0);
        glBindBuffer(GL_COPY_WRITE_BUFFER, 0);

        return *this;
    }
    */

    void do_bind(GLuint index) const override {
        glBindBuffer(type, index);
    }

    template <typename T>
    void data(const std::vector<T>& t) {
        auto s = get_scoped();
        auto in_size = t.size() * sizeof(T);
        if (in_size != size) {
            size = in_size;
            glBufferData(type, in_size, t.data(), mode);
        } else {
            glBufferSubData(type, 0, in_size, t.data());
        }
    }

private:
    size_t size{0};
};

using StaticVBO = BufferObject<GL_ARRAY_BUFFER, GL_STATIC_DRAW>;
using StaticIBO = BufferObject<GL_ELEMENT_ARRAY_BUFFER, GL_STATIC_DRAW>;
using DynamicVBO = BufferObject<GL_ARRAY_BUFFER, GL_DYNAMIC_DRAW>;
using DynamicIBO = BufferObject<GL_ELEMENT_ARRAY_BUFFER, GL_DYNAMIC_DRAW>;
