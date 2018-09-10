//
//  constant speed.hpp
//  Simpleton Engine
//
//  Created by Indi Kernick on 26/11/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_camera_2d_constant_speed_hpp
#define engine_camera_2d_constant_speed_hpp

#include "animate.hpp"

namespace Cam2D {
  template <PropID PROP>
  class ConstantSpeed final : public Animate<PROP> {
  public:
    using Type = PropType<PROP>;
    
    ConstantSpeed() = default;
    explicit ConstantSpeed(const float speed)
      : speed(speed) {}
    
    void setSpeed(const float newSpeed) {
      speed = newSpeed;
    }
  
  private:
    float speed = 1.0f;
    
    Type getMoveDistance(Props, const Params params, Type) override {
      return speed * params.delta;
    }
  };
  
  using PosConstantSpeed = ConstantSpeed<PropID::POS>;
  using ZoomConstantSpeed = ConstantSpeed<PropID::ZOOM>;
  using AngleConstantSpeed = ConstantSpeed<PropID::ANGLE>;
}

#endif
