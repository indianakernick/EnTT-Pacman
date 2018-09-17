//
//  transform.hpp
//  Simpleton Engine
//
//  Created by Indi Kernick on 13/9/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#ifndef engine_grid_transform_hpp
#define engine_grid_transform_hpp

#include "grid.hpp"

namespace Grid {
  template <typename Tile, Coord Width, Coord Height>
  Grid<Tile, Width, Height> flip_x(const Grid<Tile, Width, Height> &);
  
  template <typename Tile, Coord Width, Coord Height>
  Grid<Tile, Width, Height> flip_y(const Grid<Tile, Width, Height> &);
  
  template <typename Tile, Coord Width, Coord Height>
  Grid<Tile, Height, Width> transpose(const Grid<Tile, Width, Height> &);
  
  template <typename Tile, Coord Width, Coord Height>
  auto flip_xy(const Grid<Tile, Width, Height> &);
  
  template <typename Tile, Coord Width, Coord Height>
  auto rot_x2y(const Grid<Tile, Width, Height> &);
  
  template <typename Tile, Coord Width, Coord Height>
  auto rot_y2x(const Grid<Tile, Width, Height> &);
}

#include "transform.inl"

#endif
