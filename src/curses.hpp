//
//  curses.cpp
//  EnTT Example
//
//  Created by Indi Kernick on 10/9/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) || defined(__CYGWIN__)

#include <pdcwin.h>
#include <curses.h>

#else

#include <ncurses.h>

#endif