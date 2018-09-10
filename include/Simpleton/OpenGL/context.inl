//
//  context.inl
//  Simpleton Engine
//
//  Created by Indi Kernick on 19/12/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "../SDL/error.hpp"

inline void GL::Context::init(SDL_Window *const newWindow) {
  window = newWindow;
  initImpl(false);
}

inline void GL::Context::initVSync(SDL_Window *const newWindow) {
  window = newWindow;
  minFrameTime = 1000 / (getMonitorFPS() + 10);
  initImpl(true);
}

inline void GL::Context::initLimitFPS(SDL_Window *const newWindow, const uint32_t fps) {
  window = newWindow;
  if (getMonitorFPS() == fps) {
    minFrameTime = 1000 / (fps + 10);
    initImpl(true);
  } else {
    minFrameTime = 1000 / fps;
    initImpl(false);
  }
}

inline void GL::Context::quit() {
  #ifdef EMSCRIPTEN
  SDL_DestroyRenderer(renderer);
  #else
  SDL_GL_DeleteContext(context);
  #endif
  window = nullptr;
  minFrameTime = 0;
}

inline void GL::Context::preRender() {
  glm::ivec2 size;
  SDL_GetWindowSize(window, &size.x, &size.y);
  glViewport(0, 0, size.x, size.y);
  CHECK_OPENGL_ERROR();

  #ifdef EMSCRIPTEN
  
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
  SDL_RenderClear(renderer);
  
  #else
  
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
  CHECK_OPENGL_ERROR();
  glClearDepth(1.0f);
  CHECK_OPENGL_ERROR();
  glClearStencil(0);
  CHECK_OPENGL_ERROR();
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
  CHECK_OPENGL_ERROR();
  
  #endif
}

inline void GL::Context::postRender(const bool skipTiming) {
  if (skipTiming || minFrameTime == 0) {
    present();
  } else {
    const Uint32 start = SDL_GetTicks();
    present();
    const Uint32 end = SDL_GetTicks();
    
    const Uint32 swapTime = end - start;
    if (swapTime < minFrameTime) {
      SDL_Delay(minFrameTime - swapTime);
    }
  }
}

inline glm::ivec2 GL::Context::getFrameSize() const {
  glm::ivec2 size;
  #ifdef EMSCRIPTEN
  SDL_GetRendererOutputSize(renderer, &size.x, &size.y);
  #else
  SDL_GL_GetDrawableSize(window, &size.x, &size.y);
  #endif
  return size;
}

inline uint32_t GL::Context::getMonitorFPS() const {
  SDL_DisplayMode mode;
  CHECK_SDL_ERROR(SDL_GetWindowDisplayMode(window, &mode));
  if (mode.refresh_rate <= 0) {
    return 60;
  } else {
    return mode.refresh_rate;
  }
}

inline void GL::Context::initImpl(const bool vsync) {
  #ifdef EMSCRIPTEN
  
  renderer = CHECK_SDL_NULL(SDL_CreateRenderer(
    window,
    -1,
    SDL_RENDERER_ACCELERATED
    | (vsync ? SDL_RENDERER_PRESENTVSYNC : 0)
  ));
  
  #else
  
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
  SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
  
  context = CHECK_SDL_NULL(SDL_GL_CreateContext(window));
  CHECK_SDL_ERROR(SDL_GL_SetSwapInterval(vsync));
  
  glewExperimental = GL_TRUE;
  const GLenum glewError = glewInit();
  if (glewError != GLEW_OK) {
    throw std::runtime_error(reinterpret_cast<const char *>(glewGetErrorString(glewError)));
  }
  
  CHECK_OPENGL_ERROR();
  
  #endif
}

inline void GL::Context::present() {
  #ifdef EMSCRIPTEN
  SDL_RenderPresent(renderer);
  #else
  SDL_GL_SwapWindow(window);
  #endif
}
