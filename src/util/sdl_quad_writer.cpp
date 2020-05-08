//
//  sdl_quad_writer.cpp
//  EnTT Pacman
//
//  Created by Indi Kernick on 24/4/20.
//  Copyright © 2020 Indi Kernick. All rights reserved.
//

#include "sdl_quad_writer.hpp"

#include "sdl_check.hpp"

SDL::QuadWriter::QuadWriter(
  SDL_Renderer *renderer,
  SDL_Texture *texture,
  const SpriteSheet &sheet
) : renderer{renderer},
    texture{texture},
    spritesheet{sheet},
    srcRect{0, 0, 0, 0},
    dstRect{0, 0, 0, 0},
    angle{} {}

void SDL::QuadWriter::tilePos(
  const Pos pos, const Pos size, const double ang
) {
  dstRect.x = pos.x;
  dstRect.y = pos.y;
  dstRect.w = size.x;
  dstRect.h = size.y;
  angle = ang;
}

void SDL::QuadWriter::tileTex(const SpriteRect rect) {
  // swap rect.min.y and rect.max.y
  srcRect.x = rect.min.x;
  srcRect.y = rect.max.y;
  srcRect.w = rect.max.x - rect.min.x;
  srcRect.h = rect.min.y - rect.max.y;
}

void SDL::QuadWriter::tileTex(const SpriteID id) {
  tileTex(spritesheet.get(id));
}

void SDL::QuadWriter::render() const {
  SDL_CHECK(SDL_RenderCopyEx(
    renderer, texture, &srcRect, &dstRect, angle, nullptr, SDL_FLIP_NONE
  ));
}
