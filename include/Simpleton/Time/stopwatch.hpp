//
//  stopwatch.hpp
//  Simpleton Engine
//
//  Created by Indi Kernick on 28/11/16.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef engine_time_stopwatch_hpp
#define engine_time_stopwatch_hpp

#include "get.hpp"
#include <cassert>

namespace Time {
  ///A stopwatch to record durations
  template <typename Duration>
  class StopWatch {
  private:
    enum class State : char {
      INITIAL,
      RUNNING,
      STOPPED
    };
    using Rep = typename Duration::rep;
    
  public:
    StopWatch() = default;
    explicit StopWatch(bool)
      : startPoint(getPoint<Duration>()), endPoint(), state(State::RUNNING) {}
    
    ///Starts the stopwatch
    void start() {
      assert(state != State::RUNNING);
      state = State::RUNNING;
      startPoint = getPoint<Duration>();
    }
    ///Stops the stopwatch and returns the duration
    Rep stop() {
      assert(state == State::RUNNING);
      state = State::STOPPED;
      endPoint = getPoint<Duration>();
      return (endPoint - startPoint).count();
    }
    ///Resume the stopwatch after it has been stopped, returning the duration
    Rep resume() {
      assert(state == State::STOPPED);
      state = State::RUNNING;
      startPoint += getPoint<Duration>() - endPoint;
      return (endPoint - startPoint).count();
    }
    
    ///Gets the duration. Can be called while the stopwatch is running
    Rep get() const {
      switch (state) {
        case State::INITIAL:
          return 0;
        case State::RUNNING:
          return (getPoint<Duration>() - startPoint).count();
        case State::STOPPED:
          return (endPoint - startPoint).count();
      }
    }
    ///Returns the duration and resets the stopwatch
    Rep lap() {
      assert(state == State::RUNNING);
      const Point<Duration> now = getPoint<Duration>();
      const Duration duration = now - startPoint;
      startPoint = now;
      return duration.count();
    }
    ///Returns whether the stopwatch is running (start has just been called).
    bool running() const {
      return state == State::RUNNING;
    }
    
  private:
    Point<Duration> startPoint;
    Point<Duration> endPoint;
    State state = State::INITIAL;
  };
}

#endif
