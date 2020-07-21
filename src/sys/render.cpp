//
//  render.cpp
//  EnTT Pacman
//
//  Created by Indiana Kernick on 24/9/18.
//  Copyright © 2018 Indiana Kernick. All rights reserved.
//

#include "render.hpp"

#include "comp/dir.hpp"
#include "comp/sprite.hpp"
#include "comp/position.hpp"
#include "core/constants.hpp"
#include "comp/ghost_mode.hpp"
#include "util/dir_to_pos.hpp"
#include <entt/entity/registry.hpp>

void playerRender(entt::registry &reg, SDL::QuadWriter &writer, const int frame) {
  const auto view = reg.view<Position, ActualDir, DesiredDir, PlayerSprite>();
  for (const entt::entity e : view) {
    const Pos pos = view.get<Position>(e).p * tileSize;
    const Dir actualDir = view.get<ActualDir>(e).d;
    const double angle = static_cast<double>(view.get<DesiredDir>(e).d) * 90.0;
    writer.tilePos(pos + toPos(actualDir, frame), Pos{tileSize, tileSize}, angle);
    writer.tileTex(view.get<PlayerSprite>(e).id + frame);
    writer.render();
  }
}

void ghostRender(entt::registry &reg, SDL::QuadWriter &writer, const int frame) {
  const auto view = reg.view<Position, ActualDir, GhostSprite>();
  for (const entt::entity e : view) {
    const Pos pos = view.get<Position>(e).p * tileSize;
    const Dir actualDir = view.get<ActualDir>(e).d;
    writer.tilePos(pos + toPos(actualDir, frame), Pos{tileSize, tileSize});
    const int dirOffset = (
      actualDir == Dir::none ? 0 : static_cast<int>(actualDir)
    );
    const GhostSprite sprite = view.get<GhostSprite>(e);
    if (reg.has<ChaseMode>(e) || reg.has<ScatterMode>(e)) {
      writer.tileTex(sprite.id + dirOffset);
    } else if (reg.has<ScaredMode>(e)) {
      const int scaredTimer = reg.get<ScaredMode>(e).timer;
      const int flash = (
        scaredTimer <= ghostScaredFlashTime ? (frame / ghostScaredFlashRate) % 2 : 0
      );
      writer.tileTex(animera::SpriteID::scared_beg_ + flash);
    } else if (reg.has<EatenMode>(e)) {
      writer.tileTex(animera::SpriteID::eyes_beg_ + dirOffset);
    }
    writer.render();
  }
}

void dotRender(SDL::QuadWriter &writer, const MazeState &maze) {
  for (int y = 0; y != maze.height(); ++y) {
    for (int x = 0; x != maze.width(); ++x) {
      const Tile tile = maze[{x, y}];
      writer.tilePos({x * tileSize, y * tileSize}, {tileSize, tileSize});
      if (tile == Tile::dot) {
        writer.tileTex(animera::SpriteID::dot);
      } else if (tile == Tile::energizer) {
        writer.tileTex(animera::SpriteID::energizer);
      } else {
        continue;
      }
      writer.render();
    }
  }
}

void fullRender(SDL::QuadWriter &writer, const animera::SpriteID sprite) {
  writer.tilePos({0, 0}, tilesPx);
  writer.tileTex(sprite);
  writer.render();
}
