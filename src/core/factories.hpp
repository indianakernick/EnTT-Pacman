//
//  factories.hpp
//  EnTT Pacman
//
//  Created by Indiana Kernick on 18/9/18.
//  Copyright © 2018 Indiana Kernick. All rights reserved.
//

#ifndef CORE_FACTORIES_HPP
#define CORE_FACTORIES_HPP

#include <entt/entity/fwd.hpp>
#include "../util/sprite_sheet.hpp"

// You typically don't need to store the entity ID after making an entity.
// Sometimes you do so it's probably a good idea to return the entity ID
// just in case you need it later.

entt::entity makePlayer(entt::registry &, const SpriteSheet &);
entt::entity makeBlinky(entt::registry &, const SpriteSheet &, entt::entity);
entt::entity makePinky(entt::registry &, const SpriteSheet &, entt::entity);
entt::entity makeInky(entt::registry &, const SpriteSheet &, entt::entity, entt::entity);
entt::entity makeClyde(entt::registry &, const SpriteSheet &, entt::entity);

#endif
