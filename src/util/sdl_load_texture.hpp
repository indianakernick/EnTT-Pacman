//
//  sdl_load_texture.hpp
//  EnTT Pacman
//
//  Created by Indiana Kernick on 24/4/20.
//  Copyright © 2020 Indiana Kernick. All rights reserved.
//

#ifndef UTIL_SDL_LOAD_TEXTURE_HPP
#define UTIL_SDL_LOAD_TEXTURE_HPP

#include "sprites.hpp"
#include "sdl_delete.hpp"

namespace SDL {

Texture loadTexture(SDL_Renderer *, const animera::TextureInfo &);

}

#endif
