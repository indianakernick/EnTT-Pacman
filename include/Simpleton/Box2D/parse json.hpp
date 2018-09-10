//
//  parse json.hpp
//  Simpleton Engine
//
//  Created by Indi Kernick on 29/12/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_box2d_parse_json_hpp
#define engine_box2d_parse_json_hpp

#include "json.hpp"
#include "entity id.hpp"
#include <Box2D/Box2D.h>

namespace B2 {
  /*
  The scale of a body cannot easily be changed after the body has been created.
  The scale is multiplied by each of the verticies of the fixtures as they are
  loaded from the json node. So to set a new scale, you will need to multiply
  each of the verticies by newScale/oldScale.
  
  The position and angle are properties of the body than can easily be changed
  */
  b2Body *loadBody(const json &, b2World &, glm::vec2 pos, glm::vec2 scale, float angle);
  /// Set the user data pointer to the entity ID
  void setEntity(b2Body *, ECS::EntityID);
  
  b2JointDef *loadJoint(const json &);
  /// Set the user data pointer to the entity ID
  void setEntity(b2JointDef *, ECS::EntityID);
}

#include "parse json.inl"

#endif
