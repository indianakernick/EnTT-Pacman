//
//  pursue_target.cpp
//  EnTT Pacman
//
//  Created by Indi Kernick on 22/9/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#include "pursue_target.hpp"

#include <algorithm>
#include "comp/dir.hpp"
#include "comp/target.hpp"
#include "sys/can_move.hpp"
#include "util/dir2vec.hpp"
#include "comp/position.hpp"
#include <entt/entity/registry.hpp>
#include <Simpleton/Grid/distance.hpp>

// Pacman doesn't use A*

void pursueTarget(entt::registry &reg, const MazeState &maze) {
  constexpr float inf = 1e10f;
  auto view = reg.view<Target, Position, ActualDir, DesiredDir>();
  for (const entt::entity e : view) {
    const Grid::Pos targetPos = view.get<Target>(e).p;
    // the position we are currently moving from
    const Grid::Pos pos = view.get<Position>(e).p;
    // the direction we are currently moving in
    const Grid::Dir dir = view.get<ActualDir>(e).d;
    // the position we are currently moving to
    const Grid::Pos nextPos = pos + toVec(dir);
    // distance from the 4 candiate directions to the target
    float targetDist[4] = {inf, inf, inf, inf};
    for (const Grid::Dir candDir : Grid::dir_range) {
      // can't go back the way we came
      if (candDir == Grid::opposite(dir)) {
        continue;
      }

      // can't go through walls
      if (!canMove(reg, maze, e, nextPos, candDir)) {
        continue;
      }

      const Grid::Pos candPos = nextPos + toVec(candDir);
      targetDist[Grid::toNum<size_t>(candDir)] = Grid::euclid(candPos, targetPos);
    }

    float *smallestDist = std::min_element(targetDist, targetDist + 4);
    if (smallestDist == targetDist + 4 || *smallestDist == inf) {
      view.get<DesiredDir>(e).d = dir;
      continue;
    }

    view.get<DesiredDir>(e).d = Grid::toDir(smallestDist - targetDist);
  }
}
