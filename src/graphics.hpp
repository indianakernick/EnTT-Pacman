//
//  graphics.hpp
//  EnTT Example
//
//  Created by Indi Kernick on 17/9/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#ifndef GRAPHICS_HPP
#define GRAPHICS_HPP

#include "curses.hpp"
#include "framebuf.hpp"

void initColorPairs();
Grid::Pos getWindowSize(WINDOW *);
void configureWindow(WINDOW *);
void renderScreen(WINDOW *, const ScreenBuf &);

#endif