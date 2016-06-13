#include "modern_gl_utils/drawable.h"

MatrixTreeNode::MatrixTreeNode(const MatrixTreeNode* parent)
        : parent(parent) {
}

glm::mat4 MatrixTreeNode::get_modelview_matrix() const {
    return (parent ? parent->get_modelview_matrix() : glm::mat4{}) *
           get_local_modelview_matrix();
}
