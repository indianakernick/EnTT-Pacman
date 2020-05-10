//
//  sdl_load_texture.hpp
//  EnTT Pacman
//
//  Created by Indiana Kernick on 24/4/20.
//  Copyright © 2020 Indiana Kernick. All rights reserved.
//

#include "sdl_load_texture.hpp"

#include <string>
#include <stb_image.h>
#include "sdl_check.hpp"
#include <SDL_filesystem.h>

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

Image loadImage(const char *path) {
  int width, height;
  ImageData data{stbi_load(path, &width, &height, nullptr, 4)};
  if (data == nullptr) raiseImageError();
  return {std::move(data), width, height};
}

}

SDL::Texture SDL::loadTexture(SDL_Renderer *renderer, std::string path) {
  path.insert(0, SDL_CHECK(SDL_GetBasePath()));
  Image img = loadImage(path.c_str());
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