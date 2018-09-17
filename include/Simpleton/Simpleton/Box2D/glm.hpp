//
//  glm.hpp
//  Simpleton Engine
//
//  Created by Indi Kernick on 28/12/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_box2d_glm_hpp
#define engine_box2d_glm_hpp

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/mat2x2.hpp>
#include <glm/mat3x3.hpp>
#include <Box2D/Common/b2Math.h>

namespace B2 {
  inline glm::vec2 cast(const b2Vec2 vec) {
    return {vec.x, vec.y};
  }

  inline b2Vec2 cast(const glm::vec2 vec) {
    return {vec.x, vec.y};
  }

  inline glm::vec3 cast(const b2Vec3 vec) {
    return {vec.x, vec.y, vec.z};
  }

  inline b2Vec3 cast(const glm::vec3 vec) {
    return {vec.x, vec.y, vec.z};
  }

  inline glm::mat2 cast(const b2Mat22 mat) {
    glm::mat2 out;
    out[0][0] = mat.ex.x;
    out[0][1] = mat.ey.x;
    out[1][0] = mat.ex.y;
    out[1][1] = mat.ey.y;
    return out;
  }

  inline b2Mat22 cast(const glm::mat2 mat) {
    b2Mat22 out;
    out.ex.x = mat[0][0];
    out.ey.x = mat[0][1];
    out.ex.y = mat[1][0];
    out.ey.y = mat[1][1];
    return out;
  }

  inline glm::mat3 cast(const b2Mat33 mat) {
    glm::mat3 out;
    out[0][0] = mat.ex.x;
    out[0][1] = mat.ey.x;
    out[0][2] = mat.ez.x;
    out[1][0] = mat.ex.y;
    out[1][1] = mat.ey.y;
    out[1][2] = mat.ez.y;
    out[2][0] = mat.ex.z;
    out[2][1] = mat.ey.z;
    out[2][2] = mat.ez.z;
    return out;
  }

  inline b2Mat33 cast(const glm::mat3 mat) {
    b2Mat33 out;
    out.ex.x = mat[0][0];
    out.ey.x = mat[0][1];
    out.ez.x = mat[0][2];
    out.ex.y = mat[1][0];
    out.ey.y = mat[1][1];
    out.ez.y = mat[1][2];
    out.ex.z = mat[2][0];
    out.ey.z = mat[2][1];
    out.ez.z = mat[2][2];
    return out;
  }
}

#endif
