//
//  dir to vec.hpp
//  EnTT Example
//
//  Created by Indi Kernick on 19/9/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#ifndef DIR_TO_VEC_HPP
#define DIR_TO_VEC_HPP

#include <Simpleton/Grid/dir.hpp>
#include <Simpleton/Grid/pos.hpp>

constexpr Grid::ToVec<Grid::Coord, Grid::Dir::right, Grid::Dir::down> toVec {};

#endif