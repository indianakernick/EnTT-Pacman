//
//  context.hpp
//  Simpleton Engine
//
//  Created by Indi Kernick on 19/12/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_opengl_context_hpp
#define engine_opengl_context_hpp

#include "opengl.hpp"
#include <glm/vec2.hpp>

namespace GL {
  class Context {
  public:
    Context() = default;
    
    void init(SDL_Window *);
    void initVSync(SDL_Window *);
    void initLimitFPS(SDL_Window *, uint32_t);
    void quit();
    
    void preRender();
    void postRender(bool = false);
    
    glm::ivec2 getFrameSize() const;
    uint32_t getMonitorFPS() const;
  
  private:
    #ifdef EMSCRIPTEN
    SDL_Renderer *renderer = nullptr;
    #else
    SDL_GLContext context = nullptr;
    #endif
    SDL_Window *window = nullptr;
    uint32_t minFrameTime = 0;
    
    void initImpl(bool);
    void present();
  };
}

#include "context.inl"

#endif
