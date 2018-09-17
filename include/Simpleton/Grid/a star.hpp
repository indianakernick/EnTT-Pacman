//
//  a star.hpp
//  Simpleton Engine
//
//  Created by Indi Kernick on 13/5/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#ifndef engine_grid_a_star_hpp
#define engine_grid_a_star_hpp

#include "grid.hpp"

namespace Grid {
  /// The A* search algorithm. Returns the shortest path or an empty vector if
  /// there is no path.
  template <typename Tile, Coord Width, Coord Height, typename Function>
  std::vector<Pos> astar(const Grid<Tile, Width, Height> &, Function &&, Pos, Pos);
}

#include "a star.inl"

#endif
