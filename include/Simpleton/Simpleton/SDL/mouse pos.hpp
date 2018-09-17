//
//  mouse pos.hpp
//  Simpleton Engine
//
//  Created by Indi Kernick on 23/5/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#ifndef engine_sdl_mouse_pos_hpp
#define engine_sdl_mouse_pos_hpp

#include <glm/vec2.hpp>
#include <glm/mat3x3.hpp>
#include <SDL2/SDL_events.h>

namespace SDL {
  glm::vec2 mousePos(const glm::mat3 &);
  glm::vec2 mousePos(const glm::mat3 &, const SDL_MouseButtonEvent &);
  glm::vec2 mousePos(const glm::mat3 &, const SDL_MouseMotionEvent &);
}

#include "mouse pos.inl"

#endif
