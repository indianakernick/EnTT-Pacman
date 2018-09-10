//
//  camera.hpp
//  Simpleton Engine
//
//  Created by Indi Kernick on 15/11/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_camera_2d_camera_hpp
#define engine_camera_2d_camera_hpp

#include <tuple>
#include <memory>
#include <utility>
#include "target.hpp"
#include "animate.hpp"
#include "transform.hpp"

namespace Cam2D {
  class Camera {
  public:
    Camera() = default;
    
    void setPos(glm::vec2);
    void setZoom(float);
    void setAngle(float);
    
    template <typename... Args>
    void update(Params, Args &&...);

    Transform transform;
    
  private:
    Props props;
    
    template <size_t... TARGET_IDX, size_t... ANIM_IDX, typename Tuple>
    void updateImpl(
      Params,
      std::index_sequence<TARGET_IDX...>,
      std::index_sequence<ANIM_IDX...>,
      const Tuple &
    );
  };
}

#include "camera.inl"

#endif
