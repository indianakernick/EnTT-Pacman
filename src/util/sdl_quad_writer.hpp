//
//  sdl_quad_writer.hpp
//  EnTT Pacman
//
//  Created by Indiana Kernick on 24/4/20.
//  Copyright © 2020 Indiana Kernick. All rights reserved.
//

#ifndef UTIL_SDL_QUAD_WRITER_HPP
#define UTIL_SDL_QUAD_WRITER_HPP

#include "pos.hpp"
#include "sprites.hpp"
#include <SDL_render.h>

namespace SDL {

class QuadWriter {
public:
  QuadWriter(SDL_Renderer *, SDL_Texture *);

  void tilePos(Pos, Pos, double = 0.0);
  void tileTex(animera::SpriteRect);
  void tileTex(animera::SpriteID);

  void render() const;

private:
  SDL_Renderer *renderer;
  SDL_Texture *texture;

  SDL_Rect srcRect;
  SDL_Rect dstRect;
  double angle;
};

}

#endif
