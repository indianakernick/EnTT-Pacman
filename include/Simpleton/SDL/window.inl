//
//  window.inl
//  Simpleton Engine
//
//  Created by Indi Kernick on 2/4/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "error.hpp"

inline SDL::Window::ID SDL::Window::getID() const {
  return SDL_GetWindowID(window);
}

inline void SDL::Window::title(const std::string &newTitle) {
  SDL_SetWindowTitle(window, newTitle.c_str());
}

inline std::string SDL::Window::title() const {
  return SDL_GetWindowTitle(window);
}

inline void SDL::Window::center() {
  SDL_SetWindowPosition(window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
}

inline void SDL::Window::pos(const glm::ivec2 newPos) {
  SDL_SetWindowPosition(window, newPos.x, newPos.y);
}

inline glm::ivec2 SDL::Window::pos() const {
  glm::ivec2 pos;
  SDL_GetWindowPosition(window, &pos.x, &pos.y);
  return pos;
}

inline void SDL::Window::size(glm::ivec2 newSize) {
  SDL_SetWindowSize(window, newSize.x, newSize.y);
}

inline glm::ivec2 SDL::Window::size() const {
  glm::ivec2 size;
  SDL_GetWindowSize(window, &size.x, &size.y);
  return size;
}

inline float SDL::Window::aspect() const {
  glm::ivec2 size;
  SDL_GetWindowSize(window, &size.x, &size.y);
  return static_cast<float>(size.x) / size.y;
}

inline void SDL::Window::relMouse(const bool status) {
  assert(SDL_GetMouseFocus() == window);
  CHECK_SDL_ERROR(SDL_SetRelativeMouseMode(static_cast<SDL_bool>(status)));
}

inline bool SDL::Window::relMouse() const {
  return SDL_GetRelativeMouseMode() && SDL_GetMouseFocus() == window;
}

inline void SDL::Window::raise() {
  SDL_RaiseWindow(window);
}

inline void SDL::Window::fullscreen(const bool enabled) {
  CHECK_SDL_ERROR(SDL_SetWindowFullscreen(
    window,
    enabled ? SDL_WINDOW_FULLSCREEN_DESKTOP : 0
  ));
}

inline void SDL::Window::toggleFullscreen() {
  fullscreen((SDL_GetWindowFlags(window) & SDL_WINDOW_FULLSCREEN_DESKTOP) == 0);
}
