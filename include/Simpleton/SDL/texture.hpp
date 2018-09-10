//
//  texture.hpp
//  Simpleton Engine
//
//  Created by Indi Kernick on 3/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_sdl_texture_hpp
#define engine_sdl_texture_hpp

#include "surface.hpp"
#include <glm/vec2.hpp>
#include "renderer.hpp"

namespace SDL {
  class Texture {
  public:
    UTILS_RAII_CLASS_FULL(Texture, SDL_Texture *, texture, SDL_DestroyTexture)
    
  private:
    SDL_Texture *texture;
  };
  
  inline Texture makeTexture(
    const Renderer &renderer,
    const uint32_t format,
    const SDL_TextureAccess access,
    const glm::ivec2 size
  ) {
    return Texture(CHECK_SDL_NULL(SDL_CreateTexture(
      renderer.get(), format, access, size.x, size.y
    )));
  }
  
  inline Texture makeTexture(const Renderer &renderer, const Surface &surface) {
    return Texture(CHECK_SDL_NULL(SDL_CreateTextureFromSurface(
      renderer.get(), surface.get()
    )));
  }
}

#endif
