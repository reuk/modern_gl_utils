#include "modern_gl_utils/drawable.h"

DrawableObject::DrawableObject(DrawableObject* parent)
        : parent(parent) {
}

glm::mat4 DrawableObject::get_modelview_matrix() const {
    return (parent ? parent->get_modelview_matrix() : glm::mat4{}) *
           get_local_modelview_matrix();
}
