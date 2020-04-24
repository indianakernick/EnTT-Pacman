//
//  id.hpp
//  Simpleton Engine
//
//  Created by Indi Kernick on 10/6/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#ifndef engine_sprite_id_hpp
#define engine_sprite_id_hpp

#include <cstdint>

namespace Sprite {
  using ID = uint32_t;
  constexpr ID null = ~ID{};
}

#endif
