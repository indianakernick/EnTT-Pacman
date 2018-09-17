//
//  animate.hpp
//  Simpleton Engine
//
//  Created by Indi Kernick on 26/11/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_camera_2d_animate_hpp
#define engine_camera_2d_animate_hpp

#include "props.hpp"
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/norm.hpp>
#undef GLM_ENABLE_EXPERIMENTAL

namespace Cam2D {
  template <PropID PROP_>
  class Animate {
  public:
    static constexpr PropID PROP = PROP_;
    using Type = PropType<PROP>;
  
    Animate() = default;
    virtual ~Animate() = 0;
    
    virtual Type calculate(const Props props, const Params params, const Type target) {
      const Type current = getProp<PROP>(props);
      const Type toTarget = target - current;
      const float targetDist = glm::length(toTarget);
      const float moveDist = getMoveDistance(props, params, target);
      if (targetDist <= moveDist) {
        return target;
      } else {
        return current + moveDist * toTarget / targetDist;
      }
    }
  
  private:
    virtual float getMoveDistance(Props, Params, Type) {
      return 1.0f;
    }
  };
  
  template <PropID PROP>
  inline Animate<PROP>::~Animate() {}
}

#endif
