//
//  matrix mul.hpp
//  Simpleton Engine
//
//  Created by Indi Kernick on 28/11/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_camera_2d_matrix_mul_hpp
#define engine_camera_2d_matrix_mul_hpp

#include <glm/vec2.hpp>
#include <glm/mat3x3.hpp>

namespace Cam2D {
  inline glm::vec2 mulPos(const glm::mat3 &mat, const glm::vec2 pos) {
    return mat * glm::vec3(pos.x, pos.y, 1.0f);
  }

  inline glm::vec2 mulVec(const glm::mat3 &mat, const glm::vec2 vec) {
    return mat * glm::vec3(vec.x, vec.y, 0.0f);
  }
}

#endif
