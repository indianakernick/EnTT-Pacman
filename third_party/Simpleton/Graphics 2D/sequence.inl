//
//  sequence.inl
//  Simpleton Engine
//
//  Created by Indi Kernick on 7/10/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

template <typename Depth>
inline G2D::ColorFade::ColorFade(
  const glm::vec4 from,
  const glm::vec4 to,
  const Depth dep
) : from{from}, to{to}, depth{depth(dep)} {}

inline void G2D::ColorFade::render(Section &sec, const float prog) const {
  sec.quad();
  sec.depth(depth);
  sec.tilePos({-1.0f, -1.0f}, {2.0f, 2.0f});
  sec.whitepixel();
  sec.color(glm::mix(from, to, prog));
}

template <typename Function>
inline G2D::Callback<Function>::Callback(Function &&func)
  : func{std::forward<Function>(func)} {}

template <typename Function>
inline void G2D::Callback<Function>::render(Section &, float) const {
  func();
}

template <typename Depth>
inline G2D::ShowImage::ShowImage(
  const Sprite::ID tex,
  const glm::vec2 pos,
  const glm::vec2 size,
  const Depth dep
) : tex{tex}, pos{pos}, size{size}, depth{depth(dep)} {}

inline void G2D::ShowImage::render(Section &sec, float) const {
  sec.quad();
  sec.depth(depth);
  sec.tilePos(pos, size);
  sec.tileTex(tex);
  sec.colorWhite();
}

/*

Sequence seq;
seq.pushAction<ColorFade>(1.0f, clear, black, Depth::Black);
seq.start();
seq.render(sec, delta);

*/

template <typename ActionType, typename... Args>
G2D::ActionID G2D::Sequence::actionAfterStart(const float duration, Args &&... args) {
  return actionAfter(start_action_id, duration, std::forward<Args>(args)...);
}

template <typename ActionType, typename... Args>
G2D::ActionID G2D::Sequence::actionFrameAfterStart(const float duration, Args &&... args) {
  return actionFrameAfter(start_action_id, duration, std::forward<Args>(args)...);
}

template <typename ActionType, typename... Args>
G2D::ActionID G2D::Sequence::actionAfter(
  const ActionID prev, const float duration, Args &&... args
) {
  return pushAction(prev, false, duration, std::forward<Args>(args)...);
}

template <typename ActionType, typename... Args>
G2D::ActionID G2D::Sequence::actionFrameAfter(
  const ActionID prev, const float duration, Args &&... args
) {
  return pushAction(prev, true, duration, std::forward<Args>(args)...);
}

template <typename ActionType, typename... Args>
G2D::ActionID G2D::Sequence::pushAction(
  const ActionID prev,
  const bool sameFrame,
  const float duration,
  Args &&... args
) {
  const ActionID id = static_cast<ActionID>(actions.size());
  actions.push_back({
    std::make_unique<ActionType>(std::forward<Args>(args)...),
    duration,
    0.0f,
    prev,
    ActionState::not_started,
    sameFrame
  });
  return id;
}

inline void G2D::Sequence::start() {
  state = ActionState::running;
  for (TimedAction &action : actions) {
    action.progress = 0.0f;
    if (action.prev == start_action_id) {
      action.state = ActionState::running;
    } else {
      action.state = ActionState::not_started;
    }
  }
}

inline void G2D::Sequence::render(Section &sec, const float delta) {
  if (state != ActionState::running) {
    return;
  }
  
  std::vector<ActionID> finished;
  finished.reserve(actions.size());
  
  for (ActionID id = 0; id != actions.size(); ++id) {
    renderAction(sec, delta, finished, id);
  }
  
  triggerActions(sec, delta, finished);
}

inline void G2D::Sequence::renderAction(
  Section &sec,
  const float delta,
  Finished &finished,
  const ActionID id
) {
  TimedAction &action = actions[id];
  if (action.state == ActionState::running) {
    action.action->render(sec, action.progress / action.duration);
    action.progress += delta;
    if (action.progress > action.duration) {
      action.state = ActionState::done;
      finished.push_back(id);
    }
  }
}

inline void G2D::Sequence::triggerActions(
  Section &sec,
  const float delta,
  Finished &finished
) {
  bool needToTriggerAgain = false;
  for (ActionID id = 0; id != actions.size(); ++id) {
    TimedAction &action = actions[id];
    if (action.state == ActionState::not_started) {
      if (std::find(finished.cbegin(), finished.cend(), action.prev) != finished.cend()) {
        action.state = ActionState::running;
        if (action.triggerSameFrame) {
          renderAction(sec, delta, finished, id);
          needToTriggerAgain = true;
        }
      }
    }
  }
  if (needToTriggerAgain) {
    triggerActions(sec, delta, finished);
  }
}
