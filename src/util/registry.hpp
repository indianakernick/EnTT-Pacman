//
//  registry.hpp
//  EnTT Pacman
//
//  Created by Indi Kernick on 18/9/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#ifndef UTIL_REGISTRY_HPP
#define UTIL_REGISTRY_HPP

#include <entt/entity/registry.hpp>

using DefaultRegistry = entt::basic_registry<std::uint32_t>;
using Registry = DefaultRegistry;
using Entity = Registry::entity_type;

#endif
