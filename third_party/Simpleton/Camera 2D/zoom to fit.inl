//
//  zoom to fit.inl
//  Simpleton Engine
//
//  Created by Indi Kernick on 15/11/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "props.hpp"

inline Cam2D::ZoomToFit::ZoomToFit(const glm::vec2 box)
  : box(box) {}

inline void Cam2D::ZoomToFit::setSize(const glm::vec2 newBox) {
  box = newBox;
}

inline float Cam2D::ZoomToFit::calcTarget(Props, const Params params) {
  const float boxAspect = box.x / box.y;
  if (params.aspect < boxAspect) {
    return 2.0f / box.x;
  } else {
    return 2.0f / box.y / params.aspect;
  }
}
