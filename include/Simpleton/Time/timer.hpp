//
//  timer.hpp
//  Simpleton Engine
//
//  Created by Indi Kernick on 29/11/16.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef engine_time_timer_hpp
#define engine_time_timer_hpp

#include "get.hpp"
#include <cassert>

namespace Time {
  ///A timer to count down for duration
  template <typename Duration>
  class Timer {
  private:
    enum class State : char {
      INITIAL,
      RUNNING,
      PAUSED,
      DONE
    };
    using Rep = typename Duration::rep;
    
  public:
    Timer() = default;
    
    ///Sets the duration to be counted down from when the timer starts
    void setDuration(const Rep newDuration) {
      assert(state == State::INITIAL || state == State::DONE);
      duration = newDuration;
    }
    ///Starts the timer with the set duration
    void start() {
      assert(state == State::INITIAL || state == State::DONE);
      state = State::RUNNING;
      startPoint = getPoint<Duration>();
    }
    ///Starts the timer with the duration given
    void start(const Rep newDuration) {
      assert(state == State::INITIAL || state == State::DONE);
      state = State::RUNNING;
      duration = newDuration;
      startPoint = getPoint<Duration>();
    }
    ///Pause the timer and returns the time left
    Rep pause() {
      assert(state == State::RUNNING);
      state = State::PAUSED;
      const Point<Duration> now = getPoint<Duration>();
      pausePoint = now;
      return (duration - (now - startPoint)).count();
    }
    ///Resume the timer and returns the time left
    Rep resume() {
      assert(state == State::PAUSED);
      state = State::RUNNING;
      const Rep now = getPoint<Duration>();
      //move the startPoint forward so that timeLeft is the same as it was
      //when it was paused
      startPoint += now - pausePoint;
      return (duration - (now - startPoint)).count();
    }
    ///Get the amount of time left before the timer is done
    Rep get() {
      assert(state != State::INITIAL);
      
      if (state == State::INITIAL || state == State::DONE) {
        return 0;
      }
      
      const Point<Duration> now = getPoint<Duration>();
      
      if (state == State::PAUSED) {
        startPoint += now - pausePoint;
        pausePoint = now;
      }
      
      const Duration timeLeft = duration - (now - startPoint);
      //if timeLeft overflows then we've passed the duration
      if (timeLeft > duration) {
        state = State::DONE;
        return 0;
      } else {
        return timeLeft.count();
      }
    }
    ///Checks whether the timer is done
    bool done() {
      get();
      return state == State::DONE;
    }
    
  private:
    Duration duration = 0;
    Point<Duration> startPoint = 0;
    Point<Duration> pausePoint = 0;
    State state = State::INITIAL;
  };
}

#endif
