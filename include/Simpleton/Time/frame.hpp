//
//  frame.hpp
//  Simpleton Engine
//
//  Created by Indi Kernick on 30/6/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_time_frame_hpp
#define engine_time_frame_hpp

#include <cmath>
#include <type_traits>

namespace Time {
  enum class Round {
    FLOOR,
    ROUND,
    CEIL
  };
  
  template <typename Frame, Round ROUND = Round::FLOOR, bool WRAP = false, bool REVERSE = false>
  struct ProgToFrame {
    static_assert(std::is_integral<Frame>::value);
    
    template <typename Progress>
    static std::enable_if_t<
      std::is_floating_point<Progress>::value,
      Frame
    >
    conv(Progress prog, const Frame numFrames) {
      prog = prog * static_cast<Progress>(numFrames);
      if constexpr (ROUND == Round::ROUND) {
        prog = std::round(prog);
      } else if constexpr (ROUND == Round::CEIL) {
        prog = std::ceil(prog);
      }
      Frame frame = static_cast<Frame>(prog);
      if constexpr (REVERSE) {
        frame = numFrames - 1 - frame;
      }
      if constexpr (WRAP) {
        frame = frame % numFrames;
      }
      return frame;
    }
  };
}

#endif
