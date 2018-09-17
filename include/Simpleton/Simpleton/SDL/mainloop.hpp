//
//  mainloop.hpp
//  Simpleton Engine
//
//  Created by Indi Kernick on 17/3/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#ifndef engine_sdl_mainloop_hpp
#define engine_sdl_mainloop_hpp

#ifdef EMSCRIPTEN
#include "emscripten.h"
#else
#include "../Time/main loop.hpp"
#endif

namespace SDL {
  template <typename AppClass>
  void mainloop(void *const app) {
    reinterpret_cast<AppClass *>(app)->mainloop(16'666'666);
  }

  template <typename AppClass>
  void runMainloop(AppClass *const app) {
    #ifdef EMSCRIPTEN
    
    emscripten_set_main_loop_arg(mainloop<AppClass>, app, 0, 0);
    emscripten_pause_main_loop();
    app->init();
    emscripten_cancel_main_loop();
    emscripten_set_main_loop_arg(mainloop<AppClass>, app, 0, 1);
    
    #else
    
    app->init();
    Time::Mainloop<std::chrono::nanoseconds>::varNoSync([app] (const uint64_t delta) {
      return app->mainloop(delta);
    });
    app->quit();
    
    #endif
  }
}

#endif
