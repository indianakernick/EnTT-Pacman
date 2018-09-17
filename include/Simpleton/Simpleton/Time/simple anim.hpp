//
//  simple anim.hpp
//  Simpleton Engine
//
//  Created by Indi Kernick on 6/8/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_time_simple_anim_hpp
#define engine_time_simple_anim_hpp

#include "../Math/int float.hpp"

namespace Time {
  template <typename Duration>
  class SimpleAnim {
  public:
    static_assert(std::is_arithmetic<Duration>::value);
  
    SimpleAnim() = default;
    explicit SimpleAnim(const Duration duration)
      : duration(duration) {}
  
    ///Progress the animation forward
    void advance(const Duration delta) {
      progress += delta;
    }
    ///Progress the animation backward
    void advanceRev(const Duration delta) {
      progress -= delta;
    }
    
    ///Has the playhead passed the end?
    bool overflow() const {
      return progress > duration;
    }
    ///Has the playhead passed the beginning?
    bool underflow() const {
      return progress < Duration(0);
    }
    ///How far past the end is the playhead
    Duration overflowTime() const {
      return progress - duration;
    }
    ///How far past the beginning is the playhead
    Duration underflowTime() const {
      return -progress;
    }
    ///Is the playhead at the beginning?
    bool atBegin() const {
      return progress == Duration(0);
    }
    ///Is the playhead at the end?
    bool atEnd() const {
      return progress == duration;
    }
    
    ///Stop playing when progess passes the end
    bool stopOnEnd() {
      if (progress > duration) {
        progress = duration;
        return true;
      } else {
        return false;
      }
    }
    ///Stop playing when progress passes the beginning
    bool stopOnBegin() {
      if (progress < Duration(0)) {
        progress = Duration(0);
        return true;
      } else {
        return false;
      }
    }
    
    ///Move the playhead to the beginning when the playhead passes the end
    void repeatOnOverflow() {
      if (duration == Duration(0)) {
        progress = Duration(0);
      } else {
        progress = Math::mod(progress, duration);
      }
    }
    ///Move the playhead to the end when the playhead passes the beginning
    void repeatOnUnderflow() {
      if (duration == Duration(0)) {
        progress = Duration(0);
      } else {
        progress = duration - Math::mod(duration - progress, duration);
      }
    }
    
    ///Returns true if the animation should be played in reverse
    bool reverseOnOverflow() {
      if (progress > duration) {
        progress = duration + duration - progress;
        return true;
      } else {
        return false;
      }
    }
    ///Returns true if the animation should be played forward
    bool forwardOnUnderflow() {
      if (progress < Duration(0)) {
        progress = -progress;
        return true;
      } else {
        return false;
      }
    }
    
    ///Move the playhead to the beginning
    void toBegin() {
      progress = Duration(0);
    }
    ///Move the playhead to the end
    void toEnd() {
      progress = duration;
    }
    
    ///Change the duration
    void setDuration(const Duration newDuration) {
      duration = newDuration;
    }
    ///Get the duration
    Duration getDuration() const {
      return duration;
    }
    
    ///Get the progress of the animation as a float in range 0.0-1.0
    template <typename Float>
    std::enable_if_t<
      std::is_floating_point<Float>::value,
      Float
    >
    getProgress() const {
      if (duration == Duration(0)) {
        if (progress == Duration(0)) {
          return Float(0);
        } else {
          return Math::infinity<Float>();
        }
      } else {
        return static_cast<Float>(progress) / static_cast<Float>(duration);
      }
    }
    
    ///Set the progress of the animation as a float in range 0.0-1.0
    template <typename Float>
    std::enable_if_t<
      std::is_floating_point<Float>::value,
      Float
    >
    setProgress(const Float prog) {
      progress = prog * duration;
    }
    
    ///Get the progress of the animation as a duration from the beginning
    Duration getProgressTime() const {
      return progress;
    }
    
    ///Set the progress of the animation as a duration from the beginning
    void setProgressTime(const Duration newProgress) {
      progress = newProgress;
    }
  
  private:
    Duration duration = Duration(0);
    Duration progress = Duration(0);
  };
}

#endif
