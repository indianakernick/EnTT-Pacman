//
//  blit.hpp
//  Simpleton Engine
//
//  Created by Indi Kernick on 13/9/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#ifndef engine_grid_blit_hpp
#define engine_grid_blit_hpp

#include "grid.hpp"

namespace Grid {
  template <typename Tile, Coord DstWidth, Coord DstHeight, Coord SrcWidth, Coord SrcHeight, typename Func>
  void blit(
    Grid<Tile, DstWidth, DstHeight> &,
    const Grid<Tile, SrcWidth, SrcHeight> &,
    Func &&,
    Pos = {0, 0}
  );
  
  template <typename Tile, Coord DstWidth, Coord DstHeight, Coord SrcWidth, Coord SrcHeight>
  void blit(
    Grid<Tile, DstWidth, DstHeight> &,
    const Grid<Tile, SrcWidth, SrcHeight> &,
    Pos = {0, 0}
  );
}

#include "blit.inl"

#endif
