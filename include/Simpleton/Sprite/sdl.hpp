//
//  sdl.hpp
//  Simpleton Engine
//
//  Created by Indi Kernick on 22/9/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#ifndef engine_sprite_sdl_hpp
#define engine_sprite_sdl_hpp

#include "types.hpp"
#include <SDL2/SDL_rect.h>

namespace Sprite {
  inline SDL_Rect toSDL(const Rect rect, const uint32_t length) {
    // swap rect.min.y and rect.max.y
    return {
      static_cast<int>(rect.min.x * length),
      static_cast<int>(rect.max.y * length),
      static_cast<int>((rect.max.x - rect.min.x) * length),
      static_cast<int>((rect.min.y - rect.max.y) * length)
    };
  }
}

#endif
