//
//  surface.hpp
//  Simpleton Engine
//
//  Created by Indi Kernick on 27/12/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_sdl_surface_hpp
#define engine_sdl_surface_hpp

#include <SDL2/SDL_surface.h>
#include "../Utils/generic raii.hpp"

namespace SDL {
  class Surface {
  public:
    UTILS_RAII_CLASS_FULL(Surface, SDL_Surface *, surface, SDL_FreeSurface)
    
  private:
    SDL_Surface *surface;
  };
}

#endif
