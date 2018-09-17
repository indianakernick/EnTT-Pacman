//
//  multi dim array.hpp
//  Simpleton Engine
//
//  Created by Indi Kernick on 12/6/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_utils_multi_dim_array_hpp
#define engine_utils_multi_dim_array_hpp

#include <array>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

//The formulas are from wikipedia
//https://en.wikipedia.org/wiki/Row-_and_column-major_order

//GCC 7.1 and Clang 4.0 unroll the loops and inline the call to access

//MultiDimArray is just as efficient as manually writing out
//the dimension specific formula

namespace Utils {
  template <typename Coord, size_t DIMS>
  struct CoordsTraits {
    using Coords = std::array<Coord, DIMS>;
    using AccessIndex = size_t;
    
    static const Coords ZERO;
    
    static bool anyLess(const Coords left, const Coords right) {
      for (size_t i = 0; i != DIMS; i++) {
        if (left[i] < right[i]) {
          return true;
        }
      }
      return false;
    }
  };
  
  template <typename Coord, size_t DIMS>
  const std::array<Coord, DIMS> CoordsTraits<Coord, DIMS>::ZERO = []{
    std::array<Coord, DIMS> coords;
    for (size_t i = 0; i != DIMS; i++) {
      coords[i] = Coord(0);
    }
    return coords;
  }();

  template <typename Coord>
  struct CoordsTraits<Coord, 1> {
    using Coords = Coord;
    using AccessIndex = size_t;
    
    static const Coord ZERO;
    
    static bool anyLess(const Coords left, const Coords right) {
      return left < right;
    }
  };
  
  template <typename Coord>
  const Coord CoordsTraits<Coord, 1>::ZERO = Coord(0);
  
  template <typename Coord>
  struct CoordsTraits<Coord, 2> {
    using Coords = glm::tvec2<Coord>;
    using AccessIndex = typename Coords::length_type;
    
    static const Coords ZERO;
    
    static bool anyLess(const Coords left, const Coords right) {
      return left.x < right.x || left.y < right.y;
    }
  };
  
  template <typename Coord>
  const glm::tvec2<Coord> CoordsTraits<Coord, 2>::ZERO = {Coord(0), Coord(0)};
  
  template <typename Coord>
  struct CoordsTraits<Coord, 3> {
    using Coords = glm::tvec3<Coord>;
    using AccessIndex = typename Coords::length_type;
    
    static const Coords ZERO;
    
    static bool anyLess(const Coords left, const Coords right) {
      return left.x < right.x || left.y < right.y || left.z < right.z;
    }
  };
  
  template <typename Coord>
  const glm::tvec3<Coord> CoordsTraits<Coord, 3>::ZERO = {Coord(0), Coord(0), Coord(0)};
  
  template <typename Coord>
  struct CoordsTraits<Coord, 4> {
    using Coords = glm::tvec4<Coord>;
    using AccessIndex = typename Coords::length_type;
    
    static const Coords ZERO;
    
    static bool anyLess(const Coords left, const Coords right) {
      return left.x < right.x || left.y < right.y || left.z < right.z || left.w < right.w;
    }
  };
  
  template <typename Coord>
  const glm::tvec4<Coord> CoordsTraits<Coord, 4>::ZERO = {Coord(0), Coord(0), Coord(0), Coord(0)};
  
  class BadPos final : public std::out_of_range {
  public:
    inline BadPos()
      : std::out_of_range("Position out of range") {}
  };
  
  class BadSize final : public std::out_of_range {
  public:
    inline BadSize()
      : std::out_of_range("Size out of range") {}
  };
  
  class BadIndex final : public std::out_of_range {
  public:
    inline BadIndex()
      : std::out_of_range("Index out of range") {}
  };
  
  enum class Order : uint8_t {
    ROW_MAJOR,
    COL_MAJOR
  };

  template <size_t DIMS, Order ORDER, typename CoordType, typename IndexType>
  struct MultiDimArray;
  
  template <size_t DIMS, typename CoordType, typename IndexType>
  struct MultiDimArray<DIMS, Order::ROW_MAJOR, CoordType, IndexType> {
    static_assert(DIMS > 1);
    static_assert(std::is_integral<CoordType>::value);
    static_assert(std::is_integral<IndexType>::value);
    
    using Traits = CoordsTraits<CoordType, DIMS>;
    using AccessIndex = typename Traits::AccessIndex;
    using Coords = typename Traits::Coords;
    static constexpr size_t DIMENSIONS = DIMS;
    static constexpr Order ORDER = Order::ROW_MAJOR;
    using Coord = CoordType;
    using Index = IndexType;
  
    MultiDimArray() = delete;
    ~MultiDimArray() = delete;
    
    static Index posToIndex(const Coords pos, const Coords size) {
      if (Traits::anyLess(pos, Traits::ZERO) || Traits::anyLess(size, pos)) {
        throw BadPos();
      }
    
      Index sum = 0;
      for (AccessIndex p = 0; p != DIMS; p++) {
        Index product = static_cast<Index>(pos[p]);
        for (AccessIndex s = p + 1; s != DIMS; s++) {
          product *= size[s];
        }
        sum += product;
      }
      return sum;
    }
    
    static Coords indexToPos(const Index index, const Coords size) {
      if (index <= Index(0)) {
        throw BadIndex();
      }
    
      Coords pos;
      pos[AccessIndex(DIMS - 1)] = index % size[AccessIndex(DIMS - 1)];
      Coord product = 1;
      for (AccessIndex p = DIMS - 2; p != -AccessIndex(1); p--) {
        product *= size[p + 1];
        pos[p] = static_cast<Coord>(index / product);
      }
      return pos;
    }
    
    static Coords nextPos(Coords pos, const Coords size, const Coord advance = 1) {
      pos[AccessIndex(DIMS - 1)] += advance;
      return normalizePos(pos, size);
    }
    
    static Coords prevPos(Coords pos, const Coords size, const Coord advance = 1) {
      pos[AccessIndex(DIMS - 1)] -= advance;
      return normalizePos(pos, size);
    }
    
    static Coords nextPosAligned(Coords pos, const Coords begin, const Coords end, const Coord advance = 1) {
      pos[AccessIndex(DIMS - 1)] += advance;
      return normalizePosAligned(pos, begin, end);
    }
    
    static Coords prevPosAligned(Coords pos, const Coords begin, const Coords end, const Coord advance = 1) {
      pos[AccessIndex(DIMS - 1)] -= advance;
      return normalizePosAligned(pos, begin, end);
    }
    
    static Coords normalizePos(Coords pos, const Coords size) {
      constexpr AccessIndex FIRST = 0;
      constexpr AccessIndex SECOND = 1;
    
      for (AccessIndex p = DIMS - 1; p != FIRST; p--) {
        pos[p - AccessIndex(1)] += pos[p] / size[p];
        pos[p] %= size[p];
      }
      
      pos[FIRST] += pos[SECOND] / size[SECOND];
      
      if (pos[FIRST] >= size[FIRST]) {
        return size;
      } else {
        return pos;
      }
    }
    
    static Coords normalizePosAligned(Coords pos, const Coords begin, const Coords end) {
      constexpr AccessIndex FIRST = 0;
      constexpr AccessIndex SECOND = 1;
    
      for (AccessIndex p = DIMS - 1; p != FIRST; p--) {
        pos[p - AccessIndex(1)] += (pos[p] - begin[p]) / (end[p] - begin[p]);
        pos[p] = begin[p] + (pos[p] - begin[p]) % (end[p] - begin[p]);
      }
      
      pos[FIRST] += (pos[SECOND] - begin[SECOND]) / (end[SECOND] - begin[SECOND]);
      
      if (pos[FIRST] >= end[FIRST]) {
        return end;
      } else {
        return pos;
      }
    }
  };
  
  template <size_t DIMS, typename CoordType, typename IndexType>
  struct MultiDimArray<DIMS, Order::COL_MAJOR, CoordType, IndexType> {
    static_assert(DIMS > 1);
    static_assert(std::is_integral<CoordType>::value);
    static_assert(std::is_integral<IndexType>::value);
    
    using Traits = CoordsTraits<CoordType, DIMS>;
    using AccessIndex = typename Traits::AccessIndex;
    using Coords = typename Traits::Coords;
    static constexpr size_t DIMENSIONS = DIMS;
    static constexpr Order ORDER = Order::COL_MAJOR;
    using Coord = CoordType;
    using Index = IndexType;
  
    MultiDimArray() = delete;
    ~MultiDimArray() = delete;
    
    static Index posToIndex(const Coords pos, const Coords size) {
      if (Traits::anyLess(pos, Traits::ZERO) || Traits::anyLess(size, pos)) {
        throw BadPos();
      }
    
      Index sum = 0;
      for (AccessIndex p = 0; p != DIMS; p++) {
        Index product = static_cast<Index>(pos[p]);
        for (AccessIndex s = 0; s != p; s++) {
          product *= size[s];
        }
        sum += product;
      }
      return sum;
    }
    
    static Coords indexToPos(const Index index, const Coords size) {
      if (index <= Index(0)) {
        throw BadIndex();
      }
    
      Coords pos;
      pos[AccessIndex(0)] = index % size[AccessIndex(0)];
      Coord product = 1;
      for (AccessIndex p = 1; p != DIMS; p++) {
        product *= size[p - 1];
        pos[p] = static_cast<Coord>(index / product);
      }
      return pos;
    }
    
    static Coords nextPos(Coords pos, const Coords size, const Coord advance = 1) {
      pos[AccessIndex(0)] += advance;
      return normalizePos(pos, size);
    }
    
    static Coords prevPos(Coords pos, const Coords size, const Coord advance = 1) {
      pos[AccessIndex(0)] -= advance;
      return normalizePos(pos, size);
    }
    
    static Coords nextPosAligned(Coords pos, const Coords begin, const Coords end, const Coord advance = 1) {
      pos[AccessIndex(0)] += advance;
      return normalizePosAligned(pos, begin, end);
    }
    
    static Coords prevPosAligned(Coords pos, const Coords begin, const Coords end, const Coord advance = 1) {
      pos[AccessIndex(0)] -= advance;
      return normalizePosAligned(pos, begin, end);
    }
    
    static Coords normalizePos(Coords pos, const Coords size) {
      constexpr AccessIndex LAST = DIMS - 1;
      constexpr AccessIndex BEFORE_LAST = LAST - 1;
      
      for (AccessIndex p = 0; p != BEFORE_LAST; p++) {
        pos[p + AccessIndex(1)] += pos[p] / size[p];
        pos[p] %= size[p];
      }
      
      pos[LAST] += pos[BEFORE_LAST] / size[BEFORE_LAST];
      
      if (pos[LAST] >= size[LAST]) {
        return size;
      } else {
        return pos;
      }
    }
    
    static Coords normalizePosAligned(Coords pos, const Coords begin, const Coords end) {
      constexpr AccessIndex LAST = DIMS - 1;
      constexpr AccessIndex BEFORE_LAST = LAST - 1;
      
      for (AccessIndex p = 0; p != LAST; p++) {
        pos[p + AccessIndex(1)] += (pos[p] - begin[p]) / (end[p] - begin[p]);
        pos[p] = begin[p] + (pos[p] - begin[p]) % (end[p] - begin[p]);
      }
      
      pos[LAST] += (pos[BEFORE_LAST] - begin[BEFORE_LAST]) / (end[BEFORE_LAST] - begin[BEFORE_LAST]);
      
      if (pos[LAST] >= end[LAST]) {
        return end;
      } else {
        return pos;
      }
    }
  };
}

#endif
