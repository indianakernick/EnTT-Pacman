//
//  types.hpp
//  Simpleton Engine
//
//  Created by Indi Kernick on 24/2/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#ifndef engine_sprite_types_hpp
#define engine_sprite_types_hpp

#include "id.hpp"
#include "../Math/rect.hpp"

namespace Sprite {
  using Rect = Math::RectPP<float>;
  
  class AtlasReadError final : public std::runtime_error {
  public:
    explicit AtlasReadError(const std::exception &);
  };
  
  const glm::vec2 no_whitepixel = {-1.0f, -1.0f};
}

#include "types.inl"

#endif
