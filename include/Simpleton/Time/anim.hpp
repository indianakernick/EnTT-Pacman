//
//  anim.hpp
//  Simpleton Engine
//
//  Created by Indi Kernick on 3/9/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_time_anim_hpp
#define engine_time_anim_hpp

#include "simple anim.hpp"
#include "../Math/interpolate.hpp"

namespace Time {
  template <typename Duration>
  class Anim {
  public:
    static_assert(std::is_arithmetic<Duration>::value);
    
    enum class EdgeMode : uint8_t {
      PAUSE,
      REPEAT,
      CHANGE_DIR,
      NOTHING
    };
    enum class Dir : uint8_t {
      FORWARD,
      BACKWARD
    };
    
    Anim() = default;
    explicit Anim(const Duration duration)
      : anim(duration) {}
  
    void advance(const Duration delta) {
      if (playing) {
        if (dir == Dir::FORWARD) {
          anim.advance(delta);
        } else {
          anim.advanceRev(delta);
        }
      }
    }
    
    void pauseOnEdge() {
      if (playing) {
        if (dir == Dir::FORWARD) {
          playing = !anim.stopOnEnd();
        } else {
          playing = !anim.stopOnBegin();
        }
      }
    }
    
    void repeatAfterEdge() {
      if (playing) {
        if (dir == Dir::FORWARD) {
          anim.repeatOnOverflow();
        } else {
          anim.repeatOnUnderflow();
        }
      }
    }
    
    void changeDirOnEdge() {
      if (playing) {
        const double progress = getProgress<double>();
        if (Math::odd(progress)) {
          flipDir();
        }
        setProgress(Math::normMirror(progress));
      }
    }
    
    void handleEdge(const EdgeMode edgeMode) {
             if (edgeMode == EdgeMode::PAUSE) {
        pauseOnEdge();
      } else if (edgeMode == EdgeMode::REPEAT) {
        repeatAfterEdge();
      } else if (edgeMode == EdgeMode::CHANGE_DIR) {
        changeDirOnEdge();
      }
    }
    
    void setDir(const Dir newDir) {
      dir = newDir;
    }
    void flipDir() {
      using Underlying = std::underlying_type_t<Dir>;
      dir = static_cast<Dir>(
        static_cast<Underlying>(dir) ^ Underlying(1)
      );
    }
    Dir getDir() const {
      return dir;
    }
    
    void play() {
      playing = true;
    }
    void pause() {
      playing = false;
    }
    
    void reset() {
      playing = false;
      if (dir == Dir::FORWARD) {
        anim.toBegin();
      } else {
        anim.toEnd();
      }
    }
    
    void setDuration(const Duration duration) {
      anim.setDuration(duration);
    }
    Duration getDuration() const {
      return anim.getDuration();
    }
    
    template <typename Float>
    Float getProgress() const {
      return anim.template getProgress<Float>();
    }
    
    template <typename Float>
    void setProgress(const Float prog) {
      anim.setProgress(prog);
    }
    
  private:
    SimpleAnim<Duration> anim;
    bool playing = false;
    Dir dir = Dir::FORWARD;
  };
}

#endif
