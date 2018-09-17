//
//  dir pair.hpp
//  Simpleton Engine
//
//  Created by Indi Kernick on 20/6/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_grid_dir_pair_hpp
#define engine_grid_dir_pair_hpp

#include "dir.hpp"

namespace Grid {
  ///A pair of 2D orthogonal directions
  enum class DirPair : DirType {
    //don't reoder this
  
    UP_UP,
    UP_RIGHT,
    UP_DOWN,
    UP_LEFT,
    
    RIGHT_UP,
    RIGHT_RIGHT,
    RIGHT_DOWN,
    RIGHT_LEFT,
    
    DOWN_UP,
    DOWN_RIGHT,
    DOWN_DOWN,
    DOWN_LEFT,
    
    LEFT_UP,
    LEFT_RIGHT,
    LEFT_DOWN,
    LEFT_LEFT
  };
  
  ///Construct a DirPair from two Dir
  constexpr DirPair makePair(const Dir first, const Dir second) {
    return static_cast<DirPair>((static_cast<DirType>(first) << 2) | static_cast<DirType>(second));
  }
  
  ///Get the first Dir of a DirPair
  constexpr Dir first(const DirPair pair) {
    return static_cast<Dir>(static_cast<DirType>(pair) >> 2);
  }
  
  ///Get the second Dir of a DirPair
  constexpr Dir second(const DirPair pair) {
    return static_cast<Dir>(static_cast<DirType>(pair) & DirType(0b0011));
  }
  
  ///Divide a DirPair into a std::pair<Dir, Dir>
  constexpr std::pair<Dir, Dir> splitPair(const DirPair pair) {
    return {first(pair), second(pair)};
  }
  
  ///Set the first Dir of a DirPair
  constexpr DirPair setFirst(const DirPair pair, const Dir dir) {
    return static_cast<DirPair>(
      (static_cast<DirType>(dir) << 2) |
      (static_cast<DirType>(pair) & DirType(0b0011))
    );
  }
  
  ///Set the second Dir of a DirPair
  constexpr DirPair setSecond(const DirPair pair, const Dir dir) {
    return static_cast<DirPair>(
      (static_cast<DirType>(pair) & DirType(0b1100)) |
      static_cast<DirType>(dir)
    );
  }
  
  ///Are the directions in the pair equal
  constexpr bool pairEqual(const DirPair pair) {
    return first(pair) == second(pair);
  }
  
  ///Are the directions in the pair opposite
  constexpr bool pairOpposite(const DirPair pair) {
    return pair == DirPair::UP_DOWN    ||
           pair == DirPair::RIGHT_LEFT ||
           pair == DirPair::DOWN_UP    ||
           pair == DirPair::LEFT_RIGHT;
  }
  
  ///Get the opposites of a pair
  constexpr DirPair opposite(const DirPair pair) {
    return static_cast<DirPair>(static_cast<DirType>(pair) ^ DirType(0b1010));
  }
  
  ///Get the opposite of the first dir of a pair and the second dir
  constexpr DirPair oppositeFirst(const DirPair pair) {
    return static_cast<DirPair>(static_cast<DirType>(pair) ^ DirType(0b1000));
  }
  
  ///Get the opposite of the second dir of a pair and the first dir
  constexpr DirPair oppositeSecond(const DirPair pair) {
    return static_cast<DirPair>(static_cast<DirType>(pair) ^ DirType(0b0010));
  }
  
  ///Get the axis of the first dir
  constexpr Axis getAxisFirst(const DirPair pair) {
    return static_cast<Axis>((static_cast<DirType>(pair) >> 2) & DirType(0b01));
  }
  
  ///Get the axis of the second dir
  constexpr Axis getAxisSecond(const DirPair pair) {
    return static_cast<Axis>(static_cast<DirType>(pair) & DirType(0b0001));
  }
}

#endif
