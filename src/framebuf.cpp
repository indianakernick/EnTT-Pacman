//
//  framebuf.cpp
//  EnTT Example
//
//  Created by Indi Kernick on 18/9/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#include "framebuf.hpp"

#include <Simpleton/Grid/blit.hpp>

void blit(FrameBuf &screen, const FrameBuf &sprite, const Grid::Pos pos) {
  constexpr auto copy = [] (Cell &dst, const Cell &src) {
  	if (src.ch != ' ') {
  	  dst = src;
  	}
  };
  Grid::blit(screen, sprite, copy, pos);
}