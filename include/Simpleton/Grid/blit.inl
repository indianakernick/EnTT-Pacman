//
//  blit.inl
//  Simpleton Engine
//
//  Created by Indi Kernick on 13/9/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

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
  const Coord loX = std::min(pos.x, dst.width());
  const Coord loY = std::min(pos.y, dst.height());
  const Coord hiX = std::min(loX + src.width(), dst.width());
  const Coord hiY = std::min(loY + src.height(), dst.height());
  for (Coord y = loY; y != hiY; ++y) {
    for (Coord x = loX; x != hiX; ++x) {
      dst(x, y) = src(x - pos.x, y - pos.y);
    }
  }
}
