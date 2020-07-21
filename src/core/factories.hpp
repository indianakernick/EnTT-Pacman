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

// You typically don't need to store the entity ID after making an entity.
// Sometimes you do so it's probably a good idea to return the entity ID
// just in case you need it later.

entt::entity makePlayer(entt::registry &);
entt::entity makeBlinky(entt::registry &, entt::entity);
entt::entity makePinky(entt::registry &, entt::entity);
entt::entity makeInky(entt::registry &, entt::entity, entt::entity);
entt::entity makeClyde(entt::registry &, entt::entity);

#endif
