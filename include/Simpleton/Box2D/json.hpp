//
//  json.hpp
//  Simpleton Engine
//
//  Created by Indi Kernick on 29/12/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_box2d_json_hpp
#define engine_box2d_json_hpp

#include "../Data/json.hpp"
#include <Box2D/Common/b2Math.h>

inline void from_json(const json &j, b2Vec2 &vec) {
  vec.x = j.at(0).get<float>();
  vec.y = j.at(1).get<float>();
}

#endif
