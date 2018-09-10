//
//  nanovg debug draw.hpp
//  Simpleton Engine
//
//  Created by Indi Kernick on 29/12/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_box2d_nanovg_debug_draw_hpp
#define engine_box2d_nanovg_debug_draw_hpp

#include <nanovg/nanovg.hpp>
#include <Box2D/Common/b2Draw.h>

namespace B2 {
  class DebugDrawNanoVG final : public b2Draw {
  public:
    DebugDrawNanoVG() = default;
    explicit DebugDrawNanoVG(float);

    void DrawPolygon(const b2Vec2 *, int32, const b2Color &) override;
    void DrawSolidPolygon(const b2Vec2 *, int32, const b2Color &) override;
    void DrawCircle(const b2Vec2 &, float32, const b2Color &) override;
    void DrawSolidCircle(const b2Vec2 &, float32, const b2Vec2 &, const b2Color &) override;
    void DrawSegment(const b2Vec2 &, const b2Vec2 &, const b2Color &) override;
    void DrawTransform(const b2Transform &) override;
    void DrawPoint(const b2Vec2 &, float32, const b2Color &) override;
    
    void setContext(NVGcontext *);
  
  private:
    NVGcontext *ctx = nullptr;
    float strokeWidth = 1.0f;
  };
}

#include "nanovg debug draw.inl"

#endif
