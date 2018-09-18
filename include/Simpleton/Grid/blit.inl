//
//  blit.inl
//  Simpleton Engine
//
//  Created by Indi Kernick on 13/9/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#include <type_traits>

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
  // I realise now that Coord should be signed
  // I think changing it will break stuff
  // Oh dear!
  using SCoord = std::make_signed_t<Coord>;
  constexpr auto smin = [] (const Coord a, const Coord b) -> Coord {
    return static_cast<SCoord>(a) < static_cast<SCoord>(b) ? a : b;
  };
  constexpr auto smax = [] (const Coord a, const Coord b) -> Coord {
    return static_cast<SCoord>(a) > static_cast<SCoord>(b) ? a : b;
  };

  const Coord loX = smin(pos.x, dst.width());
  const Coord loY = smin(pos.y, dst.height());
  const Coord hiX = smin(loX + src.width(), dst.width());
  const Coord hiY = smin(loY + src.height(), dst.height());
  for (Coord y = smax(loY, 0); y != smax(hiY, 0); ++y) {
    for (Coord x = smax(loX, 0); x != smax(hiX, 0); ++x) {
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
