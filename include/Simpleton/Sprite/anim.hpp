//
//  anim.hpp
//  Simpleton Engine
//
//  Created by Indi Kernick on 10/6/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#ifndef engine_sprite_anim_hpp
#define engine_sprite_anim_hpp

#include "id.hpp"
#include <type_traits>

namespace Sprite {
  class Anim {
  public:
    /// Initialize in an invalid null state
    Anim();
    /// Initialize with sprite, number of frames and running state
    Anim(ID, ID, bool = true);
    /// Initialize with sprite, number of frames, delay and running state
    Anim(ID, ID, ID, bool = true);
    
    /// Advances the animation forward by one frame if the animation is
    /// currently running.
    void incr();
    /// Advances the animation forward by one frame if the animation is
    /// currently running. Animation repeats if the frame passes the end
    void incrRepeat();
    /// Advances the animation forward by one frame if the animation is
    /// currently running. Returns true if the frame passes the end
    bool incrCheck();
    /// Advances the animation forward by one frame if the animation is
    /// currently running. Stops the animation if the frame passes the end
    void incrStop();
    
    /// Put the animation into a running state. Set the frame to 0
    void start();
    /// Put the animation into a stopped state. Set the frame to 0
    void stop();
    /// Put the animation into a running state. Leave the frame number as it is
    void resume();
    /// Put the animation into a stopped state. Leave the frame number as it is
    void pause();
    /// Toggle the running state. Leave the frame number as it is
    void toggle();
    /// Is the animation currently in a running state?
    bool running() const;
    /// Is the animation currently in a stopped state?
    bool stopped() const;
    
    /// Set the delay between frames. A delay of 2 will require two calls to
    /// incr* to advance 1 frame.
    void delay(ID);
    /// Reset delay back to default (1).
    void noDelay();
    /// Set the delay to the highest possible value. This has a similar effect
    /// to stopping
    void maxDelay();
    /// Set the delay from a speed. 0 < speed <= 1 because the animation can
    /// only be slowed
    void speed(float);
    
    /// Get the first sprite of the animation, regardless of the current frame
    ID firstSprite() const;
    /// Get the current sprite of the animation. Essentially just
    /// firstSprite() + frame()
    ID sprite() const;
    /// Get the current sprite of the animation in the given animation group
    template <typename Group = ID>
    ID sprite(Group) const;
    
    /// Get the current frame of the animaion
    ID frame() const;
    /// Get the progress of the animation from the first frame to the LAST frame
    float progressLast() const;
    /// Get the progress of the animation from the first frame to the END frame
    float progressEnd() const;
    /// Is the current frame 0?
    bool firstFrame() const;
    /// Is the current frame the last frame?
    bool lastFrame() const;
    /// Is the current frame the end frame?
    bool endFrame() const;
    
  private:
    static_assert(std::is_unsigned_v<ID>, "ID type must be unsigned");
  
    static constexpr ID running_mask = ~ID{0} >> ID{1};
    // The stopped state is stored in the most significant bit of frame_
    static constexpr ID stopped_bit = ~running_mask;
  
    ID sprite_;
    ID frames_;
    ID frame_;
    ID delay_;
  };
}

#include "anim.inl"

#endif
