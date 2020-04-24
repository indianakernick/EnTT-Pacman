//
//  sequence.hpp
//  Simpleton Engine
//
//  Created by Indi Kernick on 7/10/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#ifndef engine_graphics_2d_sequence_hpp
#define engine_graphics_2d_sequence_hpp

#include <memory>
#include "quad writer.hpp"

namespace G2D {
  class Action {
  public:
    Action() = default;
    virtual ~Action() = default;
  
    virtual void render(G2D::Section &, float) const = 0;
  };
  
  /// Fade from the first color to the second color in the specified amount
  /// of time
  class ColorFade final : public Action {
  public:
    template <typename Depth>
    ColorFade(glm::vec4, glm::vec4, Depth);
  
    void render(Section &, float) const override;
  
  private:
    glm::vec4 from;
    glm::vec4 to;
    float depth;
  };
  
  /// Wait for the specified amount of time
  class Wait final : public Action {
  public:
    Wait() = default;
    
    void render(Section &, float) const override {}
  };
  
  /// Call the given callback function and return ActionState::done
  template <typename Function>
  class Callback final : public Action {
  public:
    Callback(Function &&);
    
    void render(Section &, float) const override;
    
  private:
    Function func;
  };
  
  template <typename Function>
  Callback(Action *, Function &&) -> Callback<Function>;
  
  class ShowImage final : public Action {
  public:
    template <typename Depth>
    ShowImage(Sprite::ID, glm::vec2, glm::vec2, Depth);
    
    void render(Section &, float) const override;
    
  private:
    Sprite::ID tex;
    glm::vec2 pos;
    glm::vec2 size;
    float depth;
  };
  
  using ActionID = uint32_t;
  
  class Sequence {
  public:
    Sequence() = default;
    
    /// Start the action after Sequence::start is called
    template <typename ActionType, typename... Args>
    ActionID actionAfterStart(float, Args &&...);
    
    /// Start the action after Sequence::start is called
    template <typename ActionType, typename... Args>
    ActionID actionFrameAfterStart(float, Args &&...);
    
    /// Start the action on the same frame that the given action finishes on
    template <typename ActionType, typename... Args>
    ActionID actionAfter(ActionID, float, Args &&...);
    
    /// Start the action on the next frame that the given action finishes on
    template <typename ActionType, typename... Args>
    ActionID actionFrameAfter(ActionID, float, Args &&...);
  
    void start();
    void render(Section &, float);
  
  private:
    using ActionPtr = std::unique_ptr<Action>;
    using Finished = std::vector<ActionID>;
    
    static constexpr ActionID start_action_id = ~ActionID{};
    
    enum class ActionState {
      not_started,
      running,
      done
    };
    
    struct TimedAction {
      ActionPtr action;
      float duration;
      float progress;
      ActionID prev;
      ActionState state;
      bool triggerSameFrame;
    };
    
    std::vector<TimedAction> actions;
    ActionState state = ActionState::not_started;
    
    void renderAction(Section &, float, Finished &, ActionID);
    void triggerActions(Section &, float, Finished &);
    template <typename ActionType, typename... Args>
    ActionID pushAction(ActionID, bool, float, Args &&...);
  };
}

#include "sequence.inl"

#endif
