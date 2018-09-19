//
//  synchronizer.hpp
//  Simpleton Engine
//
//  Created by Indi Kernick on 19/9/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#ifndef engine_time_synchronizer_hpp
#define engine_time_synchronizer_hpp

#include <thread>
#include <chrono>

namespace Time {
  /// The lifetime of a Synchronizer object is a constant amount of time
  class Synchronizer {
  public:
    using Clock = std::chrono::steady_clock;
    using Duration = Clock::duration;
    using Point = Clock::time_point;
  
    explicit Synchronizer(const Duration step)
      : start{Clock::now()}, step{step} {}
    ~Synchronizer() {
      std::this_thread::sleep_for(step - (Clock::now() - start));
    }
  
  private:
    const Point start;
    const Duration step;
  };
}

#endif
