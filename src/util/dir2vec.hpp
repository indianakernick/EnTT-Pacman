//
//  dir2vec.hpp
//  EnTT Example
//
//  Created by Indi Kernick on 19/9/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#ifndef UTIL_DIR2VEC_HPP
#define UTIL_DIR2VEC_HPP

#include <Simpleton/Grid/dir.hpp>
#include <Simpleton/Grid/pos.hpp>

constexpr Grid::ToVec<Grid::Coord, Grid::Dir::right, Grid::Dir::down> toVec {};

#endif