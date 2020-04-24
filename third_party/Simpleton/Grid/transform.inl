//
//  transform.inl
//  Simpleton Engine
//
//  Created by Indi Kernick on 13/9/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#define TRANSFORM(...)                                                          \
  for (const Coord y : in.vert()) {                                             \
    for (const Coord x : in.hori()) {                                           \
      __VA_ARGS__;                                                              \
    }                                                                           \
  }

template <typename Tile, Grid::Coord Width, Grid::Coord Height>
Grid::Grid<Tile, Width, Height> Grid::flip_x(const Grid<Tile, Width, Height> &in) {
  Grid<Tile, Width, Height> out{in.size()};
  TRANSFORM(out(in.width() - x - 1, y) = in(x, y))
  return out;
}

template <typename Tile, Grid::Coord Width, Grid::Coord Height>
Grid::Grid<Tile, Width, Height> Grid::flip_y(const Grid<Tile, Width, Height> &in) {
  Grid<Tile, Width, Height> out{in.size()};
  TRANSFORM(out(x, in.height() - y - 1) = in(x, y))
  return out;
}

template <typename Tile, Grid::Coord Width, Grid::Coord Height>
Grid::Grid<Tile, Height, Width> Grid::transpose(const Grid<Tile, Width, Height> &in) {
  Grid<Tile, Height, Width> out{{in.height(), in.width()}};
  TRANSFORM(out(y, x) = in(x, y))
  return out;
}

#undef TRANSFORM

template <typename Tile, Grid::Coord Width, Grid::Coord Height>
auto Grid::flip_xy(const Grid<Tile, Width, Height> &in) {
  return flip_x(flip_y(in));
}

template <typename Tile, Grid::Coord Width, Grid::Coord Height>
auto Grid::rot_x2y(const Grid<Tile, Width, Height> &in) {
  return transpose(flip_x(in));
}

template <typename Tile, Grid::Coord Width, Grid::Coord Height>
auto Grid::rot_y2x(const Grid<Tile, Width, Height> &in) {
  return tranpose(flip_y(in));
}
