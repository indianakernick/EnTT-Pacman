//
//  rotate to.inl
//  Simpleton Engine
//
//  Created by Indi Kernick on 11/2/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

inline Cam2D::Rotate::Rotate(const float speed, const bool enabled)
  : speed_{speed}, enabled_{enabled} {}

inline void Cam2D::Rotate::speed(const float speed) {
  speed_ = speed;
}

inline void Cam2D::Rotate::enabled(const bool enabled) {
  enabled_ = enabled;
}

inline float Cam2D::Rotate::calcTarget(const Props props, const Params params) {
  if (enabled_) {
    lastAngle_ = props.angle + params.delta * speed_;
  }
  return lastAngle_;
}
