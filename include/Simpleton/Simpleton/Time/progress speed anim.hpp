//
//  progress speed anim.hpp
//  Simpleton Engine
//
//  Created by Indi Kernick on 13/11/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_time_progress_speed_anim_hpp
#define engine_time_progress_speed_anim_hpp

#include <cmath>

namespace Time {
  template <typename Float>
  class ProgSpeedAnim {
    Float progress = Float(0);
    Float speed = Float(0);
  
    static_assert(Float(0) < Float(1)/Float(2) && Float(1)/Float(2) < Float(1));
  
  public:
    ProgSpeedAnim() = default;
    explicit ProgSpeedAnim(const Float speed)
      : speed(speed) {}
    ProgSpeedAnim(const Float progress, const Float speed)
      : progress(progress), speed(speed) {}
    
//---------------------------- MODIFYING PROGRESS ----------------------------//
    
    ///Change the progress
    void setProgress(const Float newProgress) {
      progress = newProgress;
    }
    ///Advance the animation
    void advance(const Float delta) {
      progress += speed * delta;
    }
    ///Move the playhead to the beginning
    void toBegin() {
      progress = Float(0);
    }
    ///Move the playhead to the end
    void toEnd() {
      progress = Float(1);
    }
    
//----------------------------- QUERYING PROGRESS ----------------------------//
    
    ///Get the progress
    Float getProgress() const {
      return progress;
    }
    ///Is the playhead at the beginning?
    bool atBegin() const {
      return progress == Float(0);
    }
    ///Is the playhead at the end?
    bool atEnd() const {
      return progress == Float(1);
    }
    ///Has the playhead passed the end?
    bool pastEnd() const {
      return progress > Float(1);
    }
    ///Has the playhead passed the beginning?
    bool pastBegin() const {
      return progress < Float(0);
    }
    ///How far past the end is the playhead?
    Float pastEndProgress() const {
      return progress - Float(1);
    }
    ///How far past the beginning is the playhead?
    Float pastBeginProgress() const {
      return -progress;
    }
    
//------------------------------ MODIFYING SPEED -----------------------------//
    
    ///Change the speed at which the animation plays
    void setSpeed(const Float newSpeed) {
      if (newSpeed == Float(-0)) {
        speed = Float(0);
      } else {
        speed = newSpeed;
      }
    }
    ///Stop the animation from advancing and return the speed at which the
    ///animation was playing before being stopped
    Float stop() {
      const Float oldSpeed = speed;
      speed = Float(0);
      return oldSpeed;
    }
    ///Reverse the direction that the animation plays at
    void reverse() {
      if (speed != Float(0)) {
        speed = -speed;
      }
    }
    
//------------------------------ QUERYING SPEED ------------------------------//
    
    ///Get the speed
    Float getSpeed() const {
      return speed;
    }
    ///Has the animation stopped?
    bool stopped() const {
      return speed == Float(0);
    }
    ///Is the playhead moving forward?
    bool forward() const {
      return speed > Float(0);
    }
    ///Is the playhead moving backward?
    bool backward() const {
      return speed < Float(0);
    }
    
//------------------------ HANDLING INDEPENDENT EDGES ------------------------//
    
    ///Stop playing when progress passes the end
    Float stopOnEnd() {
      if (pastEnd()) {
        toEnd();
        return stop();
      } else {
        return speed;
      }
    }
    ///Stop playing when progress passes the beginning
    Float stopOnBegin() {
      if (pastBegin()) {
        toBegin();
        return stop();
      } else {
        return speed;
      }
    }
    ///Move the playhead to the beginning when the playhead passes the end
    void repeatPastEnd() {
      progress = std::fmod(progress, Float(1));
    }
    ///Move the playhead to the end when the playhead passes the beginning
    void repeatPastBegin() {
      progress = Float(1) - std::fmod(Float(1) - progress, Float(1));
    }
    ///Play the animation backward when the playhead passes the end
    void backwardPastEnd() {
      if (pastEnd()) {
        reverse();
        progress = Float(2) - progress;
      }
    }
    ///Play the animation forward when the playhead passes the beginning
    void forwardPastBegin() {
      if (pastBegin()) {
        reverse();
        progress = -progress;
      }
    }
    
//--------------------------- HANDLING BOTH EDGES ----------------------------//

    ///Stop playing when progress passes the edge
    Float stopOnEdge() {
      if (forward()) {
        return stopOnEnd();
      } else if (backward()) {
        return stopOnBegin();
      } else {
        return speed;
      }
    }
    ///Move the playhead to the opposite edge when the playhead passes the edge
    void repeatPastEdge() {
      if (forward()) {
        repeatPastEnd();
      } else if (backward()) {
        repeatPastBegin();
      }
    }
    ///Reverse the direction of the animation when the playhead passes the edge
    void reversePastEdge() {
      if (forward()) {
        backwardPastEnd();
      } else if (backward()) {
        forwardPastBegin();
      }
    }
  };
}

#endif
