#pragma once

#include "logger.h"
#include "bindable.h"

#include <vector>

template <GLuint type, GLuint mode>
class BufferObject : public Bindable {
public:
    BufferObject()
            : Bindable(0) {
        glGenBuffers(1, &index);
    }

    virtual ~BufferObject() {
        glDeleteBuffers(1, &index);
    }

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

    void do_bind(GLuint index) const override {
        glBindBuffer(type, index);
    }

    template <typename T>
    void data(const std::vector<T> &t) const {
        auto s = get_scoped();
        glBufferData(type, t.size() * sizeof(T), t.data(), mode);
    }
};

using StaticVBO = BufferObject<GL_ARRAY_BUFFER, GL_STATIC_DRAW>;
using StaticIBO = BufferObject<GL_ELEMENT_ARRAY_BUFFER, GL_STATIC_DRAW>;
using DynamicVBO = BufferObject<GL_ARRAY_BUFFER, GL_DYNAMIC_DRAW>;
using DynamicIBO = BufferObject<GL_ELEMENT_ARRAY_BUFFER, GL_DYNAMIC_DRAW>;
