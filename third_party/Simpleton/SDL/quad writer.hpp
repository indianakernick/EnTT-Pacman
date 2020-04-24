//
//  quad writer.hpp
//  Simpleton Engine
//
//  Created by Indi Kernick on 22/9/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#ifndef engine_sdl_quad_writer_hpp
#define engine_sdl_quad_writer_hpp

#include "texture.hpp"
#include "renderer.hpp"
#include "../Sprite/sheet.hpp"

namespace SDL {
  class QuadWriter {
  public:
    QuadWriter(Renderer &, const Sprite::Sheet &, const Texture &);
    
    void tilePos(glm::ivec2, glm::ivec2, double = 0.0);
    
    void tileTex(Sprite::Rect);
    void tileTex(Sprite::ID);
    
    void render() const;
    
    const Sprite::Sheet &sheet() const;
    
  private:
    Renderer &renderer;
    const Sprite::Sheet &spritesheet;
    const Texture &texture;
    
    SDL_Rect srcRect;
    SDL_Rect dstRect;
    double angle;
  };
}

#include "quad writer.inl"

#endif
