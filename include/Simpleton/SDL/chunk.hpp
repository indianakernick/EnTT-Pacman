//
//  chunk.hpp
//  Simpleton Engine
//
//  Created by Indi Kernick on 25/4/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#ifndef engine_sdl_chunk_hpp
#define engine_sdl_chunk_hpp

#include "error.hpp"
#include <SDL2/SDL_mixer.h>
#include "../Utils/generic raii.hpp"

namespace SDL {
  namespace detail {
    void deleteChunk(Mix_Chunk *);
  }
  
  class Chunk {
  public:
    UTILS_RAII_CLASS_FULL(Chunk, Mix_Chunk *, chunk, detail::deleteChunk)
    
    void play(int = -1, int = 0, int = -1);
    
  private:
    Mix_Chunk *chunk;
  };
  
  Chunk loadWAV(const char *);
}

#include "chunk.inl"

#endif
