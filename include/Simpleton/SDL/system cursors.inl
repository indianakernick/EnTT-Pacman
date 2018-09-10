//
//  system cursors.inl
//  Simpleton Engine
//
//  Created by Indi Kernick on 25/5/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#include "error.hpp"

inline void SDL::SystemCursors::load() {
  for (int i = 0; i != SDL_NUM_SYSTEM_CURSORS; ++i) {
    const auto id = static_cast<SDL_SystemCursor>(i);
    cursors.emplace_back(CHECK_SDL_NULL(SDL_CreateSystemCursor(id)));
  }
}

inline void SDL::SystemCursors::unload() {
  cursors.clear();
}

inline void SDL::SystemCursors::set(const SDL_SystemCursor cursor) {
  if (current != cursor) {
    SDL_SetCursor(cursors.at(cursor).c);
    current = cursor;
  }
}

inline void SDL::SystemCursors::setDefault() {
  if (current != SDL_NUM_SYSTEM_CURSORS) {
    SDL_SetCursor(SDL_GetDefaultCursor());
    current = SDL_NUM_SYSTEM_CURSORS;
  }
}

inline SDL_SystemCursor SDL::SystemCursors::get() const {
  return current;
}
