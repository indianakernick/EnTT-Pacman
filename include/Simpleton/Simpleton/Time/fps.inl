//
//  fps.inl
//  Simpleton Engine
//
//  Created by Indi Kernick on 16/12/16.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

inline void Time::FPS::init() {
  endLastSecond = getPoint<Duration>();
  framesLastSecond = 0;
  framesThisSecond = 0;
}

inline void Time::FPS::frame() {
  const Point<Duration> now = getPoint<Duration>();
  if (now - endLastSecond >= std::chrono::seconds(1)) {
    framesLastSecond = framesThisSecond;
    framesThisSecond = 1;
    
    const Point<Duration> secBeforeNow = now - std::chrono::seconds(1);
    do {
      endLastSecond += std::chrono::seconds(1);
    } while (endLastSecond < secBeforeNow);
  } else {
    framesThisSecond++;
  }
}

inline uint32_t Time::FPS::get() const {
  return framesLastSecond;
}
