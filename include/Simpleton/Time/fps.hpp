//
//  fps.hpp
//  Simpleton Engine
//
//  Created by Indi Kernick on 16/12/16.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef engine_time_fps_hpp
#define engine_time_fps_hpp

#include "get.hpp"

namespace Time {
  class FPS {
  private:
    using Duration = std::chrono::nanoseconds;
  
  public:
    FPS() = default;
    
    ///Call this when you want to start recording FPS
    void init();
    ///Call this every frame
    void frame();
    ///Get the number of frames presented last second
    uint32_t get() const;
    
  private:
    Point<Duration> endLastSecond;
    uint32_t framesLastSecond = 0;
    uint32_t framesThisSecond = 0;
  };
};

#include "fps.inl"

#endif
