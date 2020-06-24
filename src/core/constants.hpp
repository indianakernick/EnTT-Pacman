//
//  constants.hpp
//  EnTT Pacman
//
//  Created by Indiana Kernick on 22/9/18.
//  Copyright © 2018 Indiana Kernick. All rights reserved.
//

#ifndef CORE_CONSTANTS_HPP
#define CORE_CONSTANTS_HPP

#include "util/pos.hpp"
#include "util/dir.hpp"

// The width and height of the maze in tiles
constexpr Pos tiles = {19, 22};
// The pixel size of tiles
constexpr int tileSize = 8;
// The width and height of the maze in pixels
constexpr Pos tilesPx = tiles * tileSize;
// The amount of ticks that ghosts are scared for
constexpr int ghostScaredTime = 40;

// The amount of ticks left on the scared timer before scared ghosts
// start flashing
constexpr int ghostScaredFlashTime = 10;
// Related to flash speed. Higher is slower
constexpr int ghostScaredFlashRate = 4;

// The total number of dots that the player must eat to win the game
constexpr int dotsInMaze = 152;

// Position where the player spawns
constexpr Pos playerSpawnPos = {9, 16};
// Direction that the player is facing and moving when they spawn
constexpr Dir playerSpawnDir = Dir::left;
// A position just outside the ghost house above the door
constexpr Pos outsideHouse  = { 9,  8};

// Home positions are the places in the house where ghosts go
constexpr Pos blinkyHome    = { 9, 10};
constexpr Pos pinkyHome     = { 9, 10};
constexpr Pos inkyHome      = { 8, 10};
constexpr Pos clydeHome     = {10, 10};
// Scatter positions are targets that ghosts move towards (but never reach)
// when in scatter mode
constexpr Pos blinkyScatter = {18,  0};
constexpr Pos pinkyScatter  = { 0,  0};
constexpr Pos inkyScatter   = {18, 21};
constexpr Pos clydeScatter  = { 0, 21};

// The amount of time ghosts will be in scatter mode before switching
// to chase mode
constexpr int scatterTicks = 15;
// The amount of time ghosts will be in chase mode before switching
// to scatter mode
constexpr int chaseTicks = 40;
// The frame rate. The game speed in set as 8 times slower than the frame rate
constexpr int fps = 20;

#endif
