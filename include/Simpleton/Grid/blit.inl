//
//  blit.inl
//  Simpleton Engine
//
//  Created by Indi Kernick on 13/9/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#include <algorithm>

template <
  typename Tile,
  Grid::Coord DstWidth,
  Grid::Coord DstHeight,
  Grid::Coord SrcWidth,
  Grid::Coord SrcHeight,
  typename Func
>
void Grid::blit(
  Grid<Tile, DstWidth, DstHeight> &dst,
  const Grid<Tile, SrcWidth, SrcHeight> &src,
  Func &&copy,
  const Pos pos
) {
  const Coord loX = std::min(pos.x, dst.width());
  const Coord loY = std::min(pos.y, dst.height());
  const Coord hiX = std::min(loX + src.width(), dst.width());
  const Coord hiY = std::min(loY + src.height(), dst.height());
  for (Coord y = std::max(loY, 0); y != std::max(hiY, 0); ++y) {
    for (Coord x = std::max(loX, 0); x != std::max(hiX, 0); ++x) {
      copy(dst(x, y), src(x - pos.x, y - pos.y));
    }
  }
}

template <
  typename Tile,
  Grid::Coord DstWidth,
  Grid::Coord DstHeight,
  Grid::Coord SrcWidth,
  Grid::Coord SrcHeight
>
void Grid::blit(
  Grid<Tile, DstWidth, DstHeight> &dst,
  const Grid<Tile, SrcWidth, SrcHeight> &src,
  const Pos pos
) {
  blit(dst, src, [] (Tile &dstTile, const Tile &srcTile) {
    dstTile = srcTile;
  }, pos);
}
