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
  const Sprite::Sheet &sheet
) : renderer{renderer},
    texture{texture},
    spritesheet{sheet},
    srcRect{0, 0, 0, 0},
    dstRect{0, 0, 0, 0},
    angle{} {}

void SDL::QuadWriter::tilePos(
  const glm::ivec2 pos, const glm::ivec2 size, const double ang
) {
  dstRect.x = pos.x;
  dstRect.y = pos.y;
  dstRect.w = size.x;
  dstRect.h = size.y;
  angle = ang;
}

void SDL::QuadWriter::tileTex(const Sprite::Rect rect) {
  // swap rect.min.y and rect.max.y
  const uint32_t length = spritesheet.getLength();
  srcRect.x = rect.min.x * length;
  srcRect.y = rect.max.y * length;
  srcRect.w = (rect.max.x - rect.min.x) * length;
  srcRect.h = (rect.min.y - rect.max.y) * length;
}

void SDL::QuadWriter::tileTex(const Sprite::ID id) {
  tileTex(spritesheet.getSprite(id));
}

void SDL::QuadWriter::render() const {
  SDL_CHECK(SDL_RenderCopyEx(
    renderer, texture, &srcRect, &dstRect, angle, nullptr, SDL_FLIP_NONE
  ));
}

const Sprite::Sheet &SDL::QuadWriter::sheet() const {
  return spritesheet;
}