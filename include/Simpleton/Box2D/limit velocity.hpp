//
//  limit velocity.hpp
//  Simpleton Engine
//
//  Created by Indi Kernick on 28/12/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_box2d_limit_velocity_hpp
#define engine_box2d_limit_velocity_hpp

#include "../Math/clamp.hpp"
#include <Box2D/Common/b2Math.h>

namespace B2 {
  b2Vec2 limitVel(const b2Vec2 vel, const b2Vec2 groundVel, const b2Vec2 maxSpeed) {
    const b2Vec2 relVel = vel - groundVel;
    return {
      Math::clampMag(relVel.x, maxSpeed.x) + groundVel.x,
      Math::clampMag(relVel.y, maxSpeed.y) + groundVel.y
    };
  }

  b2Vec2 limitVel(const b2Vec2 vel, const b2Vec2 groundVel, const float maxSpeed) {
    return limitVel(vel, groundVel, {maxSpeed, maxSpeed});
  }

  b2Vec2 limitVelX(const b2Vec2 vel, const b2Vec2 groundVel, const float maxSpeed) {
    return limitVel(vel, groundVel, {maxSpeed, std::numeric_limits<float>::infinity()});
  }

  b2Vec2 limitVelY(const b2Vec2 vel, const b2Vec2 groundVel, const float maxSpeed) {
    return limitVel(vel, groundVel, {std::numeric_limits<float>::infinity(), maxSpeed});
  }
}

#endif
