//
//  curses.cpp
//  EnTT Example
//
//  Created by Indi Kernick on 10/9/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32)

// one of them will work
#include <curses.h>
#include <pdcurses.h>
#include <ncurses.h>

#else

#include <ncurses.h>

#endif