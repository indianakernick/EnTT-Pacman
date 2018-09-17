//
//  one path.hpp
//  Simpleton Engine
//
//  Created by Indi Kernick on 14/5/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#ifndef engine_grid_one_path_hpp
#define engine_grid_one_path_hpp

#include "grid.hpp"

namespace Grid {
  /// Finds the path between two points but assumes that there is only one path.
  /// Hangs on loops and returns {} on dead ends. This is much faster than A* if
  /// there is only one path.
  template <typename Tile, Coord Width, Coord Height, typename Function>
  std::vector<Pos> onePath(const Grid<Tile, Width, Height> &, Function &&, Pos, Pos);
}

#include "one path.inl"

#endif
