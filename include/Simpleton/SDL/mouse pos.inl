//
//  mouse pos.inl
//  Simpleton Engine
//
//  Created by Indi Kernick on 23/5/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#include <SDL2/SDL_mouse.h>

namespace SDL::detail {
  inline glm::vec2 mousePos(
    const glm::mat3 &toMeters,
    const glm::ivec2 pos,
    const glm::ivec2 size
  ) {
    // converting from pixels to normalized device coordinates to meters
    glm::vec2 p = pos;
    p /= glm::vec2(size);
    p *= 2.0f;
    p -= 1.0f;
    p.y = -p.y;
    p = toMeters * glm::vec3(p.x, p.y, 1.0f);
    return p;
  }
  
  inline glm::vec2 mousePos(
    const glm::mat3 &toMeters,
    const glm::ivec2 pos,
    const Uint32 windowID
  ) {
    SDL_Window *const window = SDL_GetWindowFromID(windowID);
    assert(window);
    glm::ivec2 size;
    SDL_GetWindowSize(window, &size.x, &size.y);
    return mousePos(toMeters, pos, size);
  }
}

inline glm::vec2 SDL::mousePos(const glm::mat3 &toMeters) {
  glm::ivec2 pos;
  SDL_GetMouseState(&pos.x, &pos.y);
  SDL_Window *const window = SDL_GetMouseFocus();
  glm::ivec2 size;
  SDL_GetWindowSize(window, &size.x, &size.y);
  return detail::mousePos(toMeters, pos, size);
}

inline glm::vec2 SDL::mousePos(
  const glm::mat3 &toMeters,
  const SDL_MouseButtonEvent &event
) {
  return detail::mousePos(toMeters, {event.x, event.y}, event.windowID);
}

inline glm::vec2 SDL::mousePos(
  const glm::mat3 &toMeters,
  const SDL_MouseMotionEvent &event
) {
  return detail::mousePos(toMeters, {event.x, event.y}, event.windowID);
}
