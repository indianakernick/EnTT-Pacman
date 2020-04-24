//
//  renderer.inl
//  Simpleton Engine
//
//  Created by Indi Kernick on 20/6/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "error.hpp"

inline void SDL::Renderer::setColor(const Color color) {
  CHECK_SDL_ERROR(SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a));
}

inline SDL::Color SDL::Renderer::getColor() const {
  Color color;
  CHECK_SDL_ERROR(SDL_GetRenderDrawColor(renderer, &color.r, &color.g, &color.b, &color.a));
  return color;
}

inline void SDL::Renderer::present() {
  SDL_RenderPresent(renderer);
}

inline void SDL::Renderer::clear(const Color color) {
  setColor(color);
  CHECK_SDL_ERROR(SDL_RenderClear(renderer));
}

inline SDL::Texture SDL::Renderer::texture(const SDL::Surface &surface) {
  return Texture{CHECK_SDL_NULL(SDL_CreateTextureFromSurface(
    renderer, surface.get()
  ))};
}

inline SDL::Texture SDL::Renderer::texture(const G2D::Surface &surface) {
  uint32_t format;
  if (surface.bytesPerPixel() == 4) {
    format = SDL_PIXELFORMAT_ABGR8888;
  } else if (surface.bytesPerPixel() == 3) {
    format = SDL_PIXELFORMAT_BGR888;
  } else if (surface.bytesPerPixel() == 1) {
    format = SDL_PIXELFORMAT_INDEX8;
  } else {
    format = SDL_PIXELFORMAT_UNKNOWN;
    assert(false);
  }
  Texture tex{CHECK_SDL_NULL(SDL_CreateTexture(
    renderer,
    format,
    SDL_TEXTUREACCESS_STATIC,
    surface.width(),
    surface.height()
  ))};
  CHECK_SDL_ERROR(SDL_UpdateTexture(
    tex.get(),
    nullptr,
    surface.data(),
    surface.pitch()
  ));
  return tex;
}

inline SDL::Texture SDL::Renderer::texture(const std::string_view path) {
  return texture(G2D::loadSurface(path));
}
