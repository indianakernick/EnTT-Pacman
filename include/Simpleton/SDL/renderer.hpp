//
//  renderer.hpp
//  Simpleton Engine
//
//  Created by Indi Kernick on 20/6/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_sdl_renderer_hpp
#define engine_sdl_renderer_hpp

#include "surface.hpp"
#include "texture.hpp"
#include <glm/vec4.hpp>
#include <SDL2/SDL_render.h>
#include "../Graphics 2D/load surface.hpp"

namespace SDL {
  using Color = glm::tvec4<uint8_t>;

  class Renderer {
  public:
    UTILS_RAII_CLASS_FULL(Renderer, SDL_Renderer *, renderer, SDL_DestroyRenderer)
    
    void setColor(Color);
    Color getColor() const;
  
    void present();
    void clear(Color = {0, 0, 0, 0});

    Texture texture(const SDL::Surface &);
    Texture texture(const G2D::Surface &);
    Texture texture(std::string_view);

  private:
    SDL_Renderer *renderer;
  };
}

#include "renderer.inl"

#endif
