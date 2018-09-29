//
//  constants.hpp
//  EnTT Example
//
//  Created by Indi Kernick on 22/9/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#ifndef CORE_CONSTANTS_HPP
#define CORE_CONSTANTS_HPP

#include <Simpleton/Grid/pos.hpp>
#include <Simpleton/Grid/dir.hpp>

// In a recent version of GLM, constexpr is disabled by default.
// Something to do with SSE intrinsics not being available at compile-time

// The width and height of the maze in tiles
inline const glm::ivec2 tiles = {19, 22};
// The pixel size of tiles
constexpr int tileSize = 8;
// The scale factor of the game
constexpr int scale = 4;
// The amount of ticks that ghosts are scared for
constexpr int ghostScaredTime = 40;

// The amount of ticks left on the scared timer before scared ghosts
// start flashing
constexpr int ghostScaredFlashTime = 10;
// Related to flash speed. Higher is slower
constexpr int ghostScaredFlashRate = 4;

// The total number of dots that the player must eat to win the game
constexpr int dotsInMaze = 152;

inline const Grid::Pos playerSpawnPos = {9, 16};
constexpr Grid::Dir playerSpawnDir = Grid::Dir::left;
inline const Grid::Pos outsideHouse  = { 9,  8};
inline const Grid::Pos blinkyHome    = { 9, 10};
inline const Grid::Pos pinkyHome     = { 9, 10};
inline const Grid::Pos inkyHome      = { 8, 10};
inline const Grid::Pos clydeHome     = {10, 10};
inline const Grid::Pos blinkyScatter = {18,  0};
inline const Grid::Pos pinkyScatter  = { 0,  0};
inline const Grid::Pos inkyScatter   = {18, 21};
inline const Grid::Pos clydeScatter  = { 0, 21};

constexpr int scatterTicks = 15;
constexpr int chaseTicks = 40;
// the game speed in set as 8 times slower than the frame rate
constexpr int fps = 20;

#endif