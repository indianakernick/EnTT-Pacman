//
//  json.hpp
//  Simpleton Engine
//
//  Created by Indi Kernick on 10/6/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#ifndef engine_sprite_json_hpp
#define engine_sprite_json_hpp

#include "anim.hpp"
#include "../Data/json.hpp"

namespace Sprite {
  inline void from_json(const json &j, Anim &anim) {
    const auto delay = j.find("delay");
    const auto enabled = j.find("enabled");
    anim = {
      j.at("sprite").get<ID>(),
      j.at("frames").get<ID>(),
      delay == j.cend() ? ID{1} : delay->get<ID>(),
      enabled == j.cend() ? true : enabled->get<bool>()
    };
  }
}

#endif
