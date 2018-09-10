//
//  transform.inl
//  Simpleton Engine
//
//  Created by Indi Kernick on 15/11/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include <cassert>
#include "props.hpp"
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/matrix_transform_2d.hpp>
#undef GLM_ENABLE_EXPERIMENTAL

inline void Cam2D::Transform::setOrigin(const Origin newOrigin) {
  origin = newOrigin;
}

inline void Cam2D::Transform::setInvertX(const bool newInvertX) {
  invertX = newInvertX;
}

inline void Cam2D::Transform::setInvertY(const bool newInvertY) {
  invertY = newInvertY;
}

inline void Cam2D::Transform::setSize(const glm::vec2 size) {
  boxSize = size;
}

inline glm::mat3 Cam2D::Transform::toPixels() const {
  return toPixelsMat;
}

inline glm::mat3 Cam2D::Transform::toMeters() const {
  return toMetersMat;
}

inline void Cam2D::Transform::calculate(const Props props, const Params params) {
  static const glm::mat3 I = {
    {1.0f, 0.0f, 0.0f},
    {0.0f, 1.0f, 0.0f},
    {0.0f, 0.0f, 1.0f}
  };
  const glm::mat3 originMat = glm::translate(I, calcOriginPos());
  const glm::mat3 zoomMat = glm::scale(I, glm::vec2(props.scale));
  const glm::mat3 angleMat = glm::rotate(I, props.angle);
  const glm::mat3 invertMat = glm::scale(I, calcInvertedScale());
  const glm::mat3 aspectMat = glm::scale(I, glm::vec2(1.0f, params.aspect));
  const glm::mat3 posMat = glm::translate(I, -props.pos + calcShiftedPos(params));

  toPixelsMat = originMat * zoomMat * invertMat * aspectMat * angleMat * posMat;
  toMetersMat = glm::inverse(toPixelsMat);
}

inline glm::vec2 Cam2D::Transform::calcOriginPos() const {
  switch (origin) {
    case Origin::TOP_LEFT:
      return {-1.0f, 1.0f};
    case Origin::TOP_MID:
      return {0.0f, 1.0f};
    case Origin::TOP_RIGHT:
      return {1.0f, 1.0f};
    case Origin::MID_RIGHT:
      return {1.0f, 0.0f};
    case Origin::BOTTOM_RIGHT:
      return {1.0f, -1.0f};
    case Origin::BOTTOM_MID:
      return {0.0f, -1.0f};
    case Origin::BOTTOM_LEFT:
      return {-1.0f, -1.0f};
    case Origin::MID_LEFT:
      return {-1.0f, 0.0f};
    case Origin::CENTER:
      return {0.0f, 0.0f};
    default:
      assert(false);
      return {0.0f, 0.0f};
  }
}

inline glm::vec2 Cam2D::Transform::calcInvertedScale() const {
  return {
    invertX ? -1.0f : 1.0f,
    invertY ? -1.0f : 1.0f
  };
}

inline glm::vec2 Cam2D::Transform::calcShiftedPos(const Params params) const {
  // @TODO I'm not sure if this works for all combinations of origin and invert
  if (origin == Origin::CENTER || boxSize.x == 0.0f || boxSize.y == 0.0f) {
    return {0.0f, 0.0f};
  }
  
  const float boxAspect = boxSize.x / boxSize.y;
  if (params.aspect > boxAspect) {
    if (origin == Origin::MID_RIGHT || origin == Origin::MID_LEFT) {
      return {0.0f, 0.0f};
    } else {
      return {(params.aspect - boxAspect) / 2.0f * boxSize.y, 0.0f};
    }
  } else {
    if (origin == Origin::TOP_MID || origin == Origin::BOTTOM_MID) {
      return {0.0f, 0.0f};
    } else {
      return {0.0f, (1.0f / params.aspect - 1.0f / boxAspect) / 2.0f * boxSize.x};
    }
  }
}
