//
//  morton.inl
//  Simpleton Engine
//
//  Created by Indi Kernick on 13/6/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#include <type_traits>

//https://github.com/Forceflow/libmorton

namespace Grid::detail {
  inline uint64_t splitBits(const uint32_t coord) {
    uint64_t m = coord;
    m = (m | (m << 32)) & 0x00000000FFFFFFFF;
    m = (m | (m << 16)) & 0x0000FFFF0000FFFF;
    m = (m | (m <<  8)) & 0x00FF00FF00FF00FF;
    m = (m | (m <<  4)) & 0x0F0F0F0F0F0F0F0F;
    m = (m | (m <<  2)) & 0x3333333333333333;
    m = (m | (m <<  1)) & 0x5555555555555555;
    return m;
  }
  
  inline uint32_t getSecondBits(const uint64_t morton) {
    uint64_t c = morton & 0x5555555555555555;
    c = (c ^ (c >>  1)) & 0x3333333333333333;
    c = (c ^ (c >>  2)) & 0x0F0F0F0F0F0F0F0F;
    c = (c ^ (c >>  4)) & 0x00FF00FF00FF00FF;
    c = (c ^ (c >>  8)) & 0x0000FFFF0000FFFF;
    c = (c ^ (c >> 16)) & 0x00000000FFFFFFFF;
    return static_cast<uint32_t>(c);
  }
}

inline Grid::Morton Grid::toMorton(const Pos pos) {
  static_assert(std::is_same_v<Morton, uint64_t>);
  static_assert(std::is_same_v<Coord, int32_t>);
  return detail::splitBits(pos.x) | (detail::splitBits(pos.y) << 1);
}

inline Grid::Pos Grid::fromMorton(const Morton morton) {
  static_assert(std::is_same_v<Morton, uint64_t>);
  static_assert(std::is_same_v<Coord, int32_t>);
  return {
    detail::getSecondBits(morton),
    detail::getSecondBits(morton >> 1)
  };
}
