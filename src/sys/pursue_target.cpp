//
//  pursue_target.cpp
//  EnTT Pacman
//
//  Created by Indiana Kernick on 22/9/18.
//  Copyright © 2018 Indiana Kernick. All rights reserved.
//

#include "pursue_target.hpp"

#include <algorithm>
#include "comp/dir.hpp"
#include "comp/target.hpp"
#include "sys/can_move.hpp"
#include "comp/position.hpp"
#include "util/dir_to_pos.hpp"
#include <entt/entity/registry.hpp>

// Pacman doesn't use A*

void pursueTarget(entt::registry &reg, const MazeState &maze) {
  constexpr float inf = 1e10f;
  auto view = reg.view<Target, Position, ActualDir, DesiredDir>();
  for (const entt::entity e : view) {
    const Pos targetPos = view.get<Target>(e).p;
    // the position we are currently moving from
    const Pos pos = view.get<Position>(e).p;
    // the direction we are currently moving in
    const Dir dir = view.get<ActualDir>(e).d;
    // the position we are currently moving to
    const Pos nextPos = pos + toPos(dir);
    // distance from the 4 candiate directions to the target
    float targetDist[4] = {inf, inf, inf, inf};
    for (const Dir candDir : dir_range) {
      // can't go back the way we came
      if (candDir == opposite(dir)) {
        continue;
      }

      // can't go through walls
      if (!canMove(reg, maze, e, nextPos, candDir)) {
        continue;
      }

      const Pos candPos = nextPos + toPos(candDir);
      targetDist[static_cast<std::size_t>(candDir)] = distance(candPos, targetPos);
    }

    float *smallestDist = std::min_element(targetDist, targetDist + 4);
    if (smallestDist == targetDist + 4 || *smallestDist == inf) {
      view.get<DesiredDir>(e).d = dir;
      continue;
    }

    view.get<DesiredDir>(e).d = static_cast<Dir>(smallestDist - targetDist);
  }
}
