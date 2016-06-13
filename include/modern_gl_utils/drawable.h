#pragma once

#include "glm/glm.hpp"

class Drawable {
public:
    Drawable() = default;
    Drawable(const Drawable&) = default;
    Drawable& operator=(const Drawable&) = default;
    Drawable(Drawable&&) noexcept = default;
    Drawable& operator=(Drawable&&) noexcept = default;
    virtual ~Drawable() noexcept = default;

    virtual void draw() const = 0;
};

class MatrixTreeNode {
public:
    MatrixTreeNode(const MatrixTreeNode* parent);
    MatrixTreeNode(const MatrixTreeNode&) = default;
    MatrixTreeNode& operator=(const MatrixTreeNode&) = default;
    MatrixTreeNode(MatrixTreeNode&&) noexcept = default;
    MatrixTreeNode& operator=(MatrixTreeNode&&) noexcept = default;
    virtual ~MatrixTreeNode() noexcept = default;

    virtual glm::mat4 get_local_modelview_matrix() const = 0;
    glm::mat4 get_modelview_matrix() const;

private:
    const MatrixTreeNode* parent;
};
