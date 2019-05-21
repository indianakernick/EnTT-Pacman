//
//  geom types.hpp
//  Simpleton Engine
//
//  Created by Indi Kernick on 18/3/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#ifndef engine_graphics_2d_geom_types_hpp
#define engine_graphics_2d_geom_types_hpp

#include <array>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include "../Type List/type.hpp"

namespace G2D {
  using PosType = glm::vec3;
  using TexCoordType = glm::vec2;
  using ColorType = glm::vec4;
  using ElemType = uint16_t;
  
  struct Vertex {
    PosType pos;
    TexCoordType texCoord;
    ColorType color {1.0f};
  };
  
  using Quad = std::array<Vertex, 4>;
  
  constexpr size_t QUAD_INDICIES = 6;
  constexpr size_t QUAD_VERTS = 4;
  constexpr size_t QUAD_ATTR_SIZE = sizeof(Quad);
  constexpr size_t QUAD_ELEM_SIZE = sizeof(ElemType) * QUAD_INDICIES;
  
  using Attribs = List::Type<PosType, TexCoordType, ColorType>;
}

#endif
