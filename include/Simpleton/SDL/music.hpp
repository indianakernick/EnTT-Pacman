//
//  music.hpp
//  Simpleton Engine
//
//  Created by Indi Kernick on 15/1/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#ifndef engine_sdl_music_hpp
#define engine_sdl_music_hpp

#include "error.hpp"
#include <SDL2/SDL_mixer.h>
#include "../Utils/generic raii.hpp"

namespace SDL {
  namespace detail {
    void deleteMusic(Mix_Music *);
  }
  
  class Music {
  public:
    UTILS_RAII_CLASS_FULL(Music, Mix_Music *, music, detail::deleteMusic)
    
    void play(int = 0);
    
  private:
    Mix_Music *music;
  };
  
  Music makeMusic(const char *);
}

#include "music.inl"

#endif
