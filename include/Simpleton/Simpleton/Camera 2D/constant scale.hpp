//
//  constant scale.hpp
//  Simpleton Engine
//
//  Created by Indi Kernick on 6/12/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_camera_2d_constant_scale_hpp
#define engine_camera_2d_constant_scale_hpp

#include <cmath>
#include <cassert>
#include "animate.hpp"

namespace Cam2D {
  template <PropID PROP>
  class ConstantScale final : public Animate<PROP> {
  public:
    using Type = PropType<PROP>;
    
    ConstantScale() = default;
    explicit ConstantScale(const float newScale) {
      setScale(newScale);
    }
    
    void setScale(float newScale) {
      newScale = std::abs(newScale);
      assert(0.0f < newScale && newScale <= 1.0f);
      scale = newScale;
    }
    
  private:
    float scale = 1.0f;
    
    float getMoveDistance(const Props props, const Params params, const Type target) override {
      return params.delta * scale * glm::length(target - getProp<PROP>(props));
    }
  };
  
  using PosConstantScale = ConstantScale<PropID::POS>;
  using ZoomConstantScale = ConstantScale<PropID::ZOOM>;
  using AngleConstantScale = ConstantScale<PropID::ANGLE>;
}

#endif
