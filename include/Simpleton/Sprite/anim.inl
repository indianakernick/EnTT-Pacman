//
//  anim.inl
//  Simpleton Engine
//
//  Created by Indi Kernick on 10/6/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#include <cassert>

inline Sprite::Anim::Anim()
  : sprite_{null}, frames_{0}, frame_{0}, delay_{0} {}

inline Sprite::Anim::Anim(
  const ID sprite,
  const ID frames,
  const bool enabled
) : sprite_{sprite},
    frames_{frames},
    frame_{enabled ? 0 : stopped_bit},
    delay_{1} {
  assert(sprite_ != null);
  assert(frames_ != 0);
}

inline Sprite::Anim::Anim(
  const ID sprite,
  const ID frames,
  const ID delay,
  const bool enabled
) : sprite_{sprite},
    frames_{frames},
    frame_{enabled ? 0 : stopped_bit},
    delay_{delay} {
  assert(sprite_ != null);
  assert(frames_ != 0);
  assert(delay_ != 0);
}

inline void Sprite::Anim::incr() {
  if (running()) {
    assert(frame_ < frames_ * delay_);
    ++frame_;
  }
}

inline void Sprite::Anim::incrRepeat() {
  if (running()) {
    assert(frame_ < frames_ * delay_);
    frame_ = (frame_ + 1) % (frames_ * delay_);
  }
}

inline bool Sprite::Anim::incrCheck() {
  if (running()) {
    assert(frame_ < frames_ * delay_);
    ++frame_;
    const bool end = (frame_ == frames_ * delay_);
    frame_ -= end;
    return end;
  } else {
    return false;
  }
}

inline void Sprite::Anim::incrStop() {
  if (running()) {
    assert(frame_ < frames_ * delay_);
    ++frame_;
    if (frame_ == frames_ * delay_) {
      stop();
    }
  }
}

inline void Sprite::Anim::start() {
  frame_ = 0;
}

inline void Sprite::Anim::stop() {
  frame_ = stopped_bit;
}

inline void Sprite::Anim::resume() {
  frame_ &= running_mask;
}

inline void Sprite::Anim::pause() {
  frame_ |= stopped_bit;
}

inline void Sprite::Anim::toggle() {
  frame_ ^= stopped_bit;
}

inline bool Sprite::Anim::running() const {
  return (frame_ & stopped_bit) == 0;
}

inline bool Sprite::Anim::stopped() const {
  return (frame_ & stopped_bit) != 0;
}

inline void Sprite::Anim::delay(const ID delay) {
  assert(delay != 0);
  assert(delay_ != 0);
  if (running()) {
    frame_ /= delay_;
    frame_ *= delay;
  }
  delay_ = delay;
}

inline void Sprite::Anim::noDelay() {
  delay(1);
}

inline void Sprite::Anim::maxDelay() {
  delay(~ID{0} / frames_);
}

inline void Sprite::Anim::speed(const float speed) {
  assert(0.0f < speed && speed <= 1.0f);
  delay(1.0f / speed + 0.5f);
}

inline Sprite::ID Sprite::Anim::firstSprite() const {
  return sprite_;
}

inline Sprite::ID Sprite::Anim::sprite() const {
  assert(sprite_ != null);
  assert(frame() < frames_);
  return sprite_ + frame();
}

template <typename Group>
Sprite::ID Sprite::Anim::sprite(const Group group) const {
  return sprite() + frames_ * static_cast<ID>(group);
}

inline Sprite::ID Sprite::Anim::frame() const {
  assert(delay_ != 0);
  return (frame_ & running_mask) / delay_;
}

inline float Sprite::Anim::progressLast() const {
  assert(frames_ != 0);
  if (frames_ == 1) {
    return 0.0f;
  } else {
    return static_cast<float>(frame_ & running_mask) / ((frames_ - 1) * delay_);
  }
}

inline float Sprite::Anim::progressEnd() const {
  assert(frames_ != 0);
  return static_cast<float>(frame_ & running_mask) / (frames_ * delay_);
}

inline bool Sprite::Anim::firstFrame() const {
  return frame_ == 0;
}

inline bool Sprite::Anim::lastFrame() const {
  return frame_ == (frames_ - 1) * delay_;
}

inline bool Sprite::Anim::endFrame() const {
  return frame_ == frames_ * delay_;
}
