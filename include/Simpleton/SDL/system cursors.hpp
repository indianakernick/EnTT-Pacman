//
//  system cursors.hpp
//  Simpleton Engine
//
//  Created by Indi Kernick on 25/5/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#ifndef engine_sdl_system_cursors_hpp
#define engine_sdl_system_cursors_hpp

#include <vector>
#include <SDL2/SDL_mouse.h>
#include "../Utils/generic raii.hpp"

namespace SDL {
  class SystemCursors {
  public:
    /// Load all SDL_SystemCursors
    void load();
    /// Unload all SDL_SystemCursors
    void unload();
    
    /// Set the cursor to a SDL_SystemCursor. Throws std::range_error if the
    /// cursors haven't been loaded or the given ID is invalid.
    void set(SDL_SystemCursor);
    /// Set the default cursor
    void setDefault();
    /// Get the ID of the set cursor. Returns SDL_NUM_SYSTEM_CURSORS if the
    /// default cursor is set. Assumes that the cursor was set using this
    /// instance of this class
    SDL_SystemCursor get() const;
  
  private:
    struct Cursor {
      UTILS_RAII_CLASS_BASIC(Cursor, SDL_Cursor *, c, SDL_FreeCursor)
      SDL_Cursor *c;
    };
    std::vector<Cursor> cursors;
    SDL_SystemCursor current = SDL_NUM_SYSTEM_CURSORS;
  };
}

#include "system cursors.inl"

#endif
