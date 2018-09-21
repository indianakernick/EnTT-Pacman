//
//  window.hpp
//  Simpleton Engine
//
//  Created by Indi Kernick on 2/4/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_sdl_window_hpp
#define engine_sdl_window_hpp

#include <string>
#include <glm/vec2.hpp>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_mouse.h>
#include "../Utils/generic raii.hpp"

namespace SDL {
  class Window {
  public:
    using ID = uint32_t;
  
    struct Desc {
      std::string title;
      glm::ivec2 size = {1280, 720};
      bool resizable = false;
      bool openGL = false;
    };
  
    UTILS_RAII_CLASS_FULL(Window, SDL_Window *, window, SDL_DestroyWindow)
    
    ID getID() const;
    
    void title(const std::string &);
    std::string title() const;
    
    void center();
    void pos(glm::ivec2);
    glm::ivec2 pos() const;
    
    void size(glm::ivec2);
    glm::ivec2 size() const;
    float aspect() const;
    
    void relMouse(bool);
    bool relMouse() const;
    
    void raise();
    void fullscreen(bool);
    void toggleFullscreen();
    
  private:
    SDL_Window *window;
  };
}

#include "window.inl"

#endif
