#include "modern_gl_utils/drawable.h"

#include "glm/glm.hpp"

namespace mglu {

void drawable::draw(const glm::mat4& model_matrix) const {
    do_draw(model_matrix * get_local_model_matrix());
}

}  // namespace mglu
