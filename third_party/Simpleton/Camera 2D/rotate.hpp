//
//  rotate to.hpp
//  Simpleton Engine
//
//  Created by Indi Kernick on 11/2/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#ifndef engine_camera_2d_rotate_hpp
#define engine_camera_2d_rotate_hpp

#include "target.hpp"

namespace Cam2D {
  class Rotate final : public Target<PropID::ANGLE> {
  public:
    Rotate() = default;
    Rotate(float, bool);
    
    /// Set rotation speed in radians per second. Positive is counter-clockwise
    void speed(float);
    void enabled(bool);
    
    float calcTarget(Props, Params) override;
  
  private:
    float lastAngle_ = 0.0f;
    float speed_ = 1.0f;
    bool enabled_ = true;
  };
}

#include "rotate.inl"

#endif
