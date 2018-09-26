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
  struct sync_fps_t {};
  constexpr sync_fps_t sync_fps {};

  /// The lifetime of a Synchronizer object is a constant amount of time
  class Synchronizer {
  public:
    using Clock = std::chrono::steady_clock;
    using Duration = Clock::duration;
    using Point = Clock::time_point;
    using Rep = Clock::rep;
  
    Synchronizer(sync_fps_t, const Rep fps)
      : Synchronizer{std::chrono::nanoseconds{1'000'000'000} / fps} {}
  
    explicit Synchronizer(const Duration step)
      : start{Clock::now()}, step{step} {}
    ~Synchronizer() {
      std::this_thread::sleep_for(step - (Clock::now() - start));
    }
    
    Synchronizer(Synchronizer &&) = default;
    Synchronizer &operator=(Synchronizer &&) = default;
  
  private:
    const Point start;
    const Duration step;
  };
}

#endif
