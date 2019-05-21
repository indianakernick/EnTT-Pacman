//
//  dir.hpp
//  Simpleton Engine
//
//  Created by Indi Kernick on 10/6/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_grid_dir_hpp
#define engine_grid_dir_hpp

#include <cctype>
#include <stdexcept>
#include <string_view>
#include <glm/vec2.hpp>

namespace Grid {
  ///The underlying type of Dir and Axis
  using DirType = uint8_t;
  ///Signed version of DirType
  using SignedDirType = std::make_signed_t<DirType>;
  
  static_assert(std::is_unsigned_v<DirType>);
  static_assert(std::is_signed_v<SignedDirType>);
  
  ///A 2D orthogonal direction
  enum class Dir : DirType {
    //don't reoder this
    
    up,
    right,
    down,
    left,
    count,
    
    north = up,
    east = right,
    south = down,
    west = left,
    
    top = up,
    bottom = down,
    
    forward = up,
    backward = down,
    
    min = up,
    max = left,
    
    begin = min,
    end = count,
    
    r_begin = max,
    r_end = DirType(-1),
    
    ///A direction that represents "no direction". Not many functions explicitly
    ///handle none
    none = DirType(-count)
  };
  
  struct DirRange {
    static constexpr Dir begin() {
      return Dir::begin;
    }
    static constexpr Dir end() {
      return Dir::end;
    }
  };
  
  ///A range for iterating directions in a loop. Iterates in the order:
  ///up, right, down, left
  constexpr DirRange dir_range = {};
  
  enum class Axis : DirType {
    //don't reoder this
    
    vert,
    hori,
    count,
    
    vertical = vert,
    horizontal = hori,
    
    up_down = vert,
    left_right = hori,
    
    ///An axis that represents "no axis". Not many functions explicitly
    ///handle none
    none = DirType(-count)
  };
  
  ///Convert a direction to a number
  constexpr DirType operator+(const Dir dir) {
    return static_cast<DirType>(dir);
  }
  
  ///Convert an axis to a number
  constexpr DirType operator+(const Axis axis) {
    return static_cast<DirType>(axis);
  }
  
  ///Ensure that a Dir is not Dir::NONE by returning Dir::UP instead of
  ///Dir::NONE
  constexpr Dir filterNone(const Dir dir) {
    return static_cast<Dir>(static_cast<DirType>(dir) & DirType{0b11});
  }
  
  ///Ensure that a Dir is not Dir::none by returning a custom Dir instead of
  ///Dir::none
  constexpr Dir filterNoneCustom(const Dir dir, const Dir noneDir) {
    return dir == Dir::none ? noneDir : dir;
  }
  
  ///Ensure that an Axis is not Axis::NONE by returning Axis::VERT instead of
  ///Axis::NONE
  constexpr Axis filterNone(const Axis axis) {
    return static_cast<Axis>(static_cast<DirType>(axis) & DirType{0b1});
  }
  
  ///Ensure that n Axis is not Axis::none by returning a custom Axis instead of
  ///Axis::none
  constexpr Axis filterNoneCustom(const Axis axis, const Axis noneAxis) {
    return axis == Axis::none ? noneAxis : axis;
  }
  
  ///Check if a direction is valid
  constexpr bool valid(const Dir dir) {
    return dir == Dir::up ||
           dir == Dir::right ||
           dir == Dir::down ||
           dir == Dir::left;
  }
  
  ///Check if a direction is either valid or equal to Dir::NONE
  constexpr bool validOrNone(const Dir dir) {
    return valid(dir) || dir == Dir::none;
  }
  
  ///Check if an axis is valid
  constexpr bool valid(const Axis axis) {
    return axis == Axis::vert ||
           axis == Axis::hori;
  }
  
  ///Check if an axis is either valid or equal to Axis::none
  constexpr bool validOrNone(const Axis axis) {
    return valid(axis) || axis == Axis::none;
  }
  
  ///Get the opposite of a direction
  constexpr Dir opposite(const Dir dir) {
    //flip the second least significant bit
    return static_cast<Dir>(static_cast<DirType>(dir) ^ DirType{0b10});
  }
  
  ///Get the opposite of an axis
  constexpr Axis opposite(const Axis axis) {
    //flip the least significant bit
    return static_cast<Axis>(static_cast<DirType>(axis) ^ DirType{0b1});
  }
  
  ///Rotate a direction clockwise
  constexpr Dir rotateCW(const Dir dir, const DirType count = 1) {
    return static_cast<Dir>((static_cast<DirType>(dir) + count) & DirType{0b11});
  }
  
  ///Rotate a direction counter-clockwise (anti-clockwise)
  constexpr Dir rotateCCW(const Dir dir, const DirType count = 1) {
    return static_cast<Dir>((static_cast<DirType>(dir) - count) & DirType{0b11});
  }
  
  ///Rotate a direction. Clockwise if count is positive and counter-clockwise
  ///(anti-clockwise) if count is negative
  constexpr Dir rotate(const Dir dir, const SignedDirType count) {
    return rotateCW(dir, static_cast<DirType>(count));
  }
  
  ///Get the distance between directions
  constexpr DirType dist(const Dir a, const Dir b) {
    assert(valid(a) && valid(b));
    constexpr DirType table[16] = {
      0, 1, 2, 1, 1, 0, 1, 2, 2, 1, 0, 1, 1, 2, 1, 0
    };
    return table[
      (static_cast<DirType>(a) << 2) |
      static_cast<DirType>(b)
    ];
  }
  
  ///Get the difference between directions (signed distance from a to b)
  constexpr SignedDirType diff(const Dir a, const Dir b) {
    assert(valid(a) && valid(b));
    constexpr SignedDirType table[16] = {
      0, 1, 2, -1, -1, 0, 1, 2, -2, -1, 0, 1, 1, -2, -1, 0
    };
    return table[
      (static_cast<DirType>(a) << 2) |
      static_cast<DirType>(b)
    ];
  }
  
  ///Get the axis that a direction is on
  constexpr Axis getAxis(const Dir dir) {
    //get the least significant bit
    return static_cast<Axis>(static_cast<DirType>(dir) & DirType{0b01});
  }
  
  ///Determine whether a direction is on the vertical axis
  constexpr bool isVert(const Dir dir) {
    return getAxis(dir) == Axis::vert;
  }
  
  ///Determine whether a direction is on the horizontal axis
  constexpr bool isHori(const Dir dir) {
    return getAxis(dir) == Axis::hori;
  }
  
  ///Are these directions on the same axis?
  constexpr bool sameAxis(const Dir a, const Dir b) {
    return getAxis(a) == getAxis(b);
  }
  
  ///Configuration template for converting a direction to a 2D unit vector
  template <typename Number_, Dir PlusX = Dir::right, Dir PlusY = Dir::up>
  struct ToVec {
    using Number = Number_;
    static constexpr Dir plusx = PlusX;
    static constexpr Dir plusy = PlusY;
  
    static_assert(!sameAxis(plusx, plusy), "PlusX and PlusY must be on different axes");
  
    ///Convert a direction to a 2D unit vector
    glm::tvec2<Number> operator()(const Dir dir, const Number dist = Number{1}) const {
      constexpr Number zero{0};
      
      switch (dir) {
        case plusx:
          return {dist, zero};
        case opposite(plusx):
          return {-dist, zero};
        case plusy:
          return {zero, dist};
        case opposite(plusy):
          return {zero, -dist};
        case Dir::none:
          return {zero, zero};
        
        default:
          throw std::invalid_argument("Invalid direction");
      }
    }
  };
  
  // Grid::ToVec<int>{}(Grid::Dir::up, 2)
  // Grid::toVec(Grid::Dir::up, 2)
  
  ///Helper for converting directions to 2D unit vectors
  template <typename Number>
  constexpr ToVec<Number> toVec {};
  
  ///Configuration template for converting a 2D unit vector to a direction
  template <Dir PlusX = Dir::right, Dir PlusY = Dir::up, bool Exact = true>
  struct FromVec {
    static constexpr Dir plusx = PlusX;
    static constexpr Dir plusy = PlusY;
    static constexpr bool exact = Exact;
  
    static_assert(!sameAxis(plusx, plusy), "PlusX and PlusY must be on different axes");
    
    ///Convert a 2D unit vector to a direction
    template <typename Number>
    constexpr Dir operator()(const glm::tvec2<Number> vec, const Number dist = Number{1}) const {
      using Vec = glm::tvec2<Number>;
      constexpr Number zero{0};
      
      if constexpr (exact) {
      
               if (vec == Vec(dist, zero)) {
          return plusx;
        } else if (vec == Vec(-dist, zero)) {
          return opposite(plusx);
        } else if (vec == Vec(zero, dist)) {
          return plusy;
        } else if (vec == Vec(zero, -dist)) {
          return opposite(plusy);
        } else {
          throw std::invalid_argument("Vector cannot be converted to direction");
        }
        
      } else {
        
        if (vec.x == vec.y) {
          throw std::invalid_argument("Vector cannot be converted to direction");
        }
        if (std::abs(vec.x) > std::abs(vec.y)) {
          if (vec.x > zero) {
            return plusx;
          } else {
            return opposite(plusx);
          }
        } else {
          if (vec.y > zero) {
            return plusy;
          } else {
            return opposite(plusy);
          }
        }
        
      }
    }
  };
  
  // Grid::FromVec{}(vec, 1)
  // Grid::fromVec(vec, 1)
  
  ///Helper for converting 2D unit vectors to directions
  constexpr FromVec fromVec {};
  
  ///Helper for converting inexact 2D unit vectors to directions
  constexpr FromVec<Dir::right, Dir::up, false> fromVarVec {};
  
  ///Convert a direction to a number
  template <typename Number>
  constexpr Number toNum(const Dir dir) {
    return static_cast<Number>(dir);
  }
  
  ///Convert a direction to a number and multiply
  template <typename Number>
  constexpr Number toNum(const Dir dir, const Number factor) {
    return static_cast<Number>(dir) * factor;
  }
  
  ///Convert a number to a direction
  template <typename Number>
  constexpr Dir toDir(const Number number) {
    const Dir dir = static_cast<Dir>(number);
    assert(validOrNone(dir));
    return dir;
  }
  
  constexpr std::string_view toUpperCaseString(const Dir dir) {
    assert(validOrNone(dir));
    switch (dir) {
      case Dir::up:
        return "UP";
      case Dir::right:
        return "RIGHT";
      case Dir::down:
        return "DOWN";
      case Dir::left:
        return "LEFT";
      case Dir::none:
        return "NONE";
      default:
        return "";
    }
  }
  
  constexpr std::string_view toLowerCaseString(const Dir dir) {
    assert(validOrNone(dir));
    switch (dir) {
      case Dir::up:
        return "up";
      case Dir::right:
        return "right";
      case Dir::down:
        return "down";
      case Dir::left:
        return "left";
      case Dir::none:
        return "none";
      default:
        return "";
    }
  }
  
  constexpr Dir toDir(const std::string_view str) {
    //Case insensitive comparison. Assumes other is lower case
    const auto equalTo = [str] (const std::string_view other) {
      if (str.size() != other.size()) {
        return false;
      }
      for (size_t i = 0; i != str.size(); ++i) {
        if (std::tolower(str[i]) != other[i]) {
          return false;
        }
      }
      return true;
    };
    
    if (str.size() == 0) {
      return Dir::none;
    } else if (equalTo("up")) {
      return Dir::up;
    } else if (equalTo("right")) {
      return Dir::right;
    } else if (equalTo("down")) {
      return Dir::down;
    } else if (equalTo("left")) {
      return Dir::left;
    } else {
      return Dir::none;
    }
  }
  
  ///Get the next direction. Used for iterating directions
  constexpr Dir next(const Dir dir) {
    return static_cast<Dir>(static_cast<DirType>(dir) + DirType{1});
  }
  
  ///Get the previous direction. Used for iterating directions in reverse
  constexpr Dir prev(const Dir dir) {
    return static_cast<Dir>(static_cast<DirType>(dir) - DirType{1});
  }
  
  ///Get the next direction. Used for iterating directions
  constexpr Dir &operator++(Dir &dir) {
    return dir = next(dir);
  }

  ///Get the previous direction. Used for iterating directions in reverse
  constexpr Dir &operator--(Dir &dir) {
    return dir = prev(dir);
  }
  
  ///Dereference a direction. Used for iterating directions
  constexpr Dir operator*(const Dir dir) {
    assert(valid(dir));
    return dir;
  }
}

#endif
