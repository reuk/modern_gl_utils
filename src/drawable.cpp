#include "modern_gl_utils/drawable.h"

#include "glm/glm.hpp"

void Drawable::draw(const glm::mat4& modelview_matrix) const {
    do_draw(modelview_matrix * get_local_modelview_matrix());
}
