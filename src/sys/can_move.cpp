//
//  can_move.cpp
//  EnTT Pacman
//
//  Created by Indi Kernick on 27/9/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#include "can_move.hpp"

#include "comp/dir.hpp"
#include "comp/house.hpp"
#include "util/dir2vec.hpp"
#include "comp/position.hpp"
#include <entt/entity/registry.hpp>

bool canMove(
  entt::registry &reg,
  const MazeState &maze,
  const entt::entity e,
  const Grid::Pos pos,
  const Grid::Dir desiredDir
) {
  const Grid::Pos desiredPos = pos + toVec(desiredDir);

  if (maze.outOfRange(desiredPos)) {
    // The tunnel is the only place where playable space meets the edge of the map.
    // The movement system handles the tunnel
    return Grid::isHori(desiredDir);
  }

  // just like we assumed the position of the tunnel, we're assuming the
  // orientation of the door to the ghost house. Once again, making the door
  // into an entity is probably a more robust but more complex solution.
  // I guess this is one of those "do as I say, not as I do" situations!
  const Tile desiredTile = maze[desiredPos];
  if (desiredTile == Tile::door) {
    if (reg.has<EnterHouse>(e) && desiredDir == Grid::Dir::down) {
      return true;
    } else if (reg.has<LeaveHouse>(e) && desiredDir == Grid::Dir::up) {
       return true;
    }
  } else if (desiredTile != Tile::wall) {
    return true;
  }

  return false;
}
