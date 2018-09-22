//
//  texture.hpp
//  Simpleton Engine
//
//  Created by Indi Kernick on 3/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_sdl_texture_hpp
#define engine_sdl_texture_hpp

#include <SDL2/SDL_render.h>
#include "../Utils/generic raii.hpp"

namespace SDL {
  class Texture {
  public:
    UTILS_RAII_CLASS_FULL(Texture, SDL_Texture *, texture, SDL_DestroyTexture)
    
  private:
    SDL_Texture *texture;
  };
}

#endif
