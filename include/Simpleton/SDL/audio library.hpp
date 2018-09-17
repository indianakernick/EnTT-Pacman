//
//  audio library.hpp
//  Simpleton Engine
//
//  Created by Indi Kernick on 15/1/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#ifndef engine_sdl_audio_library_hpp
#define engine_sdl_audio_library_hpp

#include "error.hpp"
#include <SDL2/SDL_mixer.h>
#include "../Utils/generic raii.hpp"
#include "../Utils/instance limiter.hpp"

namespace SDL {
  namespace detail {
    void deleteAudioLibrary(bool);
  }
  
  class AudioLibrary final : public Utils::ForceSingleton<AudioLibrary> {
  public:
    UTILS_RAII_CLASS_FULL(AudioLibrary, bool, initialized, detail::deleteAudioLibrary)
  
  private:
    bool initialized;
  };
  
  struct AudioLibParams {
    int codecFlags = 0;
    int frequency = MIX_DEFAULT_FREQUENCY;
    Uint16 format = MIX_DEFAULT_FORMAT;
    int channels = 2;
    int chunksize = 2048;
  };
  
  AudioLibrary makeAudioLibrary(const AudioLibParams &);
}

#include "audio library.inl"

#endif
