//
//  main loop.hpp
//  Simpleton Engine
//
//  Created by Indi Kernick on 9/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_time_main_loop_hpp
#define engine_time_main_loop_hpp

#include <cmath>
#include <thread>
#include "get.hpp"
#include "stopwatch.hpp"
#include "../Math/int float.hpp"
#include "../Utils/function traits.hpp"

namespace Time {
  template <typename Duration>
  struct Mainloop {
  private:
    using Rep = typename Duration::rep;
    
  public:
    ///Call an update method with a time delta
    template <typename Function>
    static bool update(Function &&func, const Rep delta) {
      if constexpr (std::is_convertible<Utils::function_ret<Function>, bool>::value) {
        if constexpr (Utils::function_arity<Function> == 1) {
          return static_cast<bool>(func(static_cast<Utils::function_arg<Function, 0>>(delta)));
        } else {
          return static_cast<bool>(func());
        }
      } else {
        if constexpr (Utils::function_arity<Function> == 1) {
          func(static_cast<Utils::function_arg<Function, 0>>(delta));
        } else {
          func();
        }
        return true;
      }
    }
    
    template <typename Function>
    static bool updateLag(Function &&func, Rep &lag, const Rep step) {
      StopWatch<Duration> stopwatch(true);
      const bool ok = update(func, step);
      stopwatch.stop();
      if (stopwatch.get() > step) {
        lag -= stopwatch.get() - step;
      }
      return ok;
    }
    
    ///Variable time step with no synchonization
    template <typename Function>
    static void varNoSync(Function &&func) {
      Point<Duration> last = getPoint<Duration>();
      bool ok = true;
     
      while (ok) {
        const Point<Duration> now = getPoint<Duration>();
        const Rep delta = (now - last).count();
        last = now;
        
        ok = update(func, delta);
      }
    }
    
    ///Fixed time step with synchonization
    template <typename Function>
    static void fixedSync(Function &&func, const Rep step) {
      bool ok = true;
      
      while (ok) {
        const Point<Duration> start = getPoint<Duration>();
        
        ok = update(func, step);
        
        const Duration elapsed = getPoint<Duration>() - start;
        if (elapsed.count() < step) {
          #ifndef __MINGW32__
          std::this_thread::sleep_for(Duration(step) - elapsed);
          #endif
        }
      }
    }
    
    ///Fixed time step with variable pre and post (input and rendering)
    template <typename PreFunc, typename UpdateFunc, typename PostFunc>
    static void fixedWithVarPrePost(
      PreFunc &&preFunc,
      UpdateFunc &&updateFunc,
      PostFunc &&postFunc,
      const Rep step,
      const uint32_t maxSteps
    ) {
      Rep lag = 0;
      Point<Duration> last = getPoint<Duration>();
      bool ok = true;
      
      while (ok) {
        const Point<Duration> now = getPoint<Duration>();
        const Duration elapsed = now - last;
        last = now;
        lag += elapsed.count();
        
        uint32_t numSteps = lag < 0 ? 0 : std::min(static_cast<uint32_t>(lag / step), maxSteps);
        const Rep stepSize = step * numSteps;
        lag -= stepSize;
        
        ok = update(preFunc, stepSize);
        
        while (numSteps) {
          ok = ok && update(updateFunc, step);
          numSteps--;
        }
        
        ok = ok && update(postFunc, stepSize);
      }
    }
  };
}

#endif
