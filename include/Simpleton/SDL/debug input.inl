//
//  debug input.inl
//  Simpleton Engine
//
//  Created by Indi Kernick on 28/12/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include <cassert>
#include <iostream>

inline void SDL::printWindowEvent(const SDL_WindowEvent event) {
  std::cout << "Window " << event.windowID << "  ";
  
  switch (event.event) {
    case SDL_WINDOWEVENT_NONE:
      std::cout << "None\n";
      break;
    case SDL_WINDOWEVENT_SHOWN:
      std::cout << "Shown\n";
      break;
    case SDL_WINDOWEVENT_HIDDEN:
      std::cout << "Hidden\n";
      break;
    case SDL_WINDOWEVENT_EXPOSED:
      std::cout << "Exposed\n";
      break;
    case SDL_WINDOWEVENT_MOVED:
      std::cout << "Moved to " << event.data1 << ", " << event.data2 << '\n';
      break;
    case SDL_WINDOWEVENT_RESIZED:
      std::cout << "Resized to " << event.data1 << "x" << event.data2 << '\n';
      break;
    case SDL_WINDOWEVENT_SIZE_CHANGED:
      std::cout << "Size changed to " << event.data1 << "x" << event.data2 << '\n';
      break;
    case SDL_WINDOWEVENT_MINIMIZED:
      std::cout << "Minimized\n";
      break;
    case SDL_WINDOWEVENT_MAXIMIZED:
      std::cout << "Maximized\n";
      break;
    case SDL_WINDOWEVENT_RESTORED:
      std::cout << "Restored\n";
      break;
    case SDL_WINDOWEVENT_ENTER:
      std::cout << "Enter\n";
      break;
    case SDL_WINDOWEVENT_LEAVE:
      std::cout << "Leave\n";
      break;
    case SDL_WINDOWEVENT_FOCUS_GAINED:
      std::cout << "Focus gained\n";
      break;
    case SDL_WINDOWEVENT_FOCUS_LOST:
      std::cout << "Focus lost\n";
      break;
    case SDL_WINDOWEVENT_CLOSE:
      std::cout << "Close\n";
      break;
    case SDL_WINDOWEVENT_TAKE_FOCUS:
      std::cout << "Take focus\n";
      break;
    case SDL_WINDOWEVENT_HIT_TEST:
      std::cout << "Hit test\n";
      break;
    default:
      assert(false);
  }
}

inline void SDL::printEvent(const SDL_Event event) {
  switch (event.type) {
    case SDL_WINDOWEVENT:
      printWindowEvent(event.window);
      break;
  }
}

inline void SDL::printWindowFlags(const uint32_t flags) {
  #define CHECK(flag, name) \
  if (flags & SDL_WINDOW_##flag) { \
    std::cout << #name ", "; \
  }
  
  CHECK(FULLSCREEN        , Fullscreen        )
  CHECK(OPENGL            , OpenGL            )
  CHECK(SHOWN             , Shown             )
  CHECK(HIDDEN            , Hidden            )
  CHECK(BORDERLESS        , Borderless        )
  CHECK(RESIZABLE         , Resizable         )
  CHECK(MINIMIZED         , Minimized         )
  CHECK(MAXIMIZED         , Maximized         )
  CHECK(INPUT_GRABBED     , Input Grabbed     )
  CHECK(INPUT_FOCUS       , Input Focus       )
  CHECK(MOUSE_FOCUS       , Mouse Focus       )
  CHECK(FULLSCREEN_DESKTOP, Fullscreen Desktop)
  CHECK(FOREIGN           , Foreign           )
  CHECK(ALLOW_HIGHDPI     , Allow High DPI    )
  CHECK(MOUSE_CAPTURE     , Mouse Capture     )
  CHECK(ALWAYS_ON_TOP     , Always on Top     )
  CHECK(SKIP_TASKBAR      , Skip Taskbar      )
  CHECK(UTILITY           , Utility           )
  CHECK(TOOLTIP           , Tooltip           )
  CHECK(POPUP_MENU        , Popup Menu        )
  
  #undef CHECK
  
  std::cout << '\n';
}
