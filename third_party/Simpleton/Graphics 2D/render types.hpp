//
//  render types.hpp
//  Simpleton Engine
//
//  Created by Indi Kernick on 18/3/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#ifndef engine_graphics_2d_render_types_hpp
#define engine_graphics_2d_render_types_hpp

#include <glm/vec4.hpp>
#include <glm/mat3x3.hpp>

namespace G2D {
  using TextureID = size_t;
  
  struct QuadRange {
    size_t begin;
    size_t end;
    
    size_t size() const {
      return end - begin;
    }
  };
  
  struct RenderParams {
    glm::mat3 viewProj {
      1.0f, 0.0f, 0.0f,
      0.0f, 1.0f, 0.0f,
      0.0f, 0.0f, 1.0f
    };
    TextureID tex {0};
  };
  
  constexpr bool operator==(const RenderParams &a, const RenderParams &b) {
    return a.tex == b.tex && a.viewProj == b.viewProj;
  }
  constexpr bool operator!=(const RenderParams &a, const RenderParams &b) {
    return !(a == b);
  }
  
  enum class PlusXY {
    RIGHT_UP,
    LEFT_UP,
    RIGHT_DOWN,
    LEFT_DOWN
  };
  
  enum class MinFilter {
    NEAREST,
    LINEAR
  };
  enum class MagFilter {
    NEAREST,
    LINEAR
  };
  enum class TexWrap {
    CLAMP,
    REPEAT
  };
  
  struct TexParams {
    TexWrap wrap;
    MinFilter min;
    MagFilter mag;
  };
}

#endif
