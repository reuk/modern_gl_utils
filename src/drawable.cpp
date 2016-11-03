#include "modern_gl_utils/drawable.h"

#include "glm/glm.hpp"

namespace mglu {

void drawable::draw(const glm::mat4& modelview_matrix) const {
    do_draw(modelview_matrix * get_local_modelview_matrix());
}

}  // namespace mglu
