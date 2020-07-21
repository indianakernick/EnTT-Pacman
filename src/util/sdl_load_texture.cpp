//
//  sdl_load_texture.hpp
//  EnTT Pacman
//
//  Created by Indiana Kernick on 24/4/20.
//  Copyright © 2020 Indiana Kernick. All rights reserved.
//

#include "sdl_load_texture.hpp"

#include <stb_image.h>
#include "sdl_check.hpp"

namespace {

struct DeleteImageData {
  void operator()(unsigned char *ptr) const noexcept {
    stbi_image_free(ptr);
  }
};

using ImageData = std::unique_ptr<unsigned char, DeleteImageData>;

struct Image {
  ImageData data;
  int width, height;
};

[[noreturn]] void raiseImageError() {
  const char *error = stbi_failure_reason();
  throw std::runtime_error{error};
}

Image loadImage(const unsigned char *data, const std::size_t size) {
  int width, height;
  ImageData image{stbi_load_from_memory(data, size, &width, &height, nullptr, 4)};
  if (image == nullptr) raiseImageError();
  return {std::move(image), width, height};
}

}

SDL::Texture SDL::loadTexture(SDL_Renderer *renderer, const unsigned char *data, const std::size_t size) {
  Image img = loadImage(data, size);
  SDL::Texture tex{SDL_CHECK(SDL_CreateTexture(
    renderer,
    SDL_PIXELFORMAT_ABGR8888,
    SDL_TEXTUREACCESS_STATIC,
    img.width, img.height
  ))};
  SDL_CHECK(SDL_UpdateTexture(tex.get(), nullptr, img.data.get(), img.width * 4));
  SDL_CHECK(SDL_SetTextureBlendMode(tex.get(), SDL_BLENDMODE_BLEND));
  return tex;
}