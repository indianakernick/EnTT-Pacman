//
//  nanovg debug draw.inl
//  Simpleton Engine
//
//  Created by Indi Kernick on 29/12/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include <cmath>
#include <glm/vec2.hpp>

namespace B2::detail {
  inline b2Color brighten(const b2Color color) {
    constexpr float COEF = 1.2f;
    return {
      std::fmin(color.r * COEF, 1.0f),
      std::fmin(color.g * COEF, 1.0f),
      std::fmin(color.b * COEF, 1.0f),
      color.a,
    };
  }
  
  inline NVGcolor castColor(const b2Color color) {
    return nvgRGBAf(color.r, color.g, color.b, color.a);
  }
}

inline B2::DebugDrawNanoVG::DebugDrawNanoVG(const float strokeWidth)
  : strokeWidth(strokeWidth) {}

void B2::DebugDrawNanoVG::DrawPolygon(
  const b2Vec2 *verts,
  const int32 numVerts,
  const b2Color &color
) {
  if (ctx) {
    if (numVerts < 3) {
      return;
    }
    
    nvgBeginPath(ctx);
    nvgStrokeColor(ctx, detail::castColor(color));
    nvgStrokeWidth(ctx, strokeWidth);
    nvgMoveTo(ctx, verts[0].x, verts[0].y);
    
    const b2Vec2 *const endVerts = verts + numVerts;
    for (const b2Vec2 *v = verts + 1; v != endVerts; ++v) {
      nvgLineTo(ctx, v->x, v->y);
    }
    nvgLineTo(ctx, verts[0].x, verts[0].y);
    
    nvgStroke(ctx);
  }
}

void B2::DebugDrawNanoVG::DrawSolidPolygon(
  const b2Vec2 *verts,
  const int32 numVerts,
  const b2Color &color
) {
  if (ctx) {
    if (numVerts < 3) {
      return;
    }
    
    nvgBeginPath(ctx);
    nvgFillColor(ctx, detail::castColor(color));
    nvgMoveTo(ctx, verts[0].x, verts[0].y);
    
    const b2Vec2 *const endVerts = verts + numVerts;
    for (const b2Vec2 *v = verts + 1; v != endVerts; ++v) {
      nvgLineTo(ctx, v->x, v->y);
    }
    nvgLineTo(ctx, verts[0].x, verts[0].y);
    
    nvgFill(ctx);
  }
}

void B2::DebugDrawNanoVG::DrawCircle(
  const b2Vec2 &center,
  const float32 radius,
  const b2Color &color
) {
  if (ctx) {
    nvgBeginPath(ctx);
    nvgStrokeColor(ctx, detail::castColor(color));
    nvgStrokeWidth(ctx, strokeWidth);
    nvgCircle(ctx, center.x, center.y, radius);
    nvgStroke(ctx);
  }
}

void B2::DebugDrawNanoVG::DrawSolidCircle(
  const b2Vec2 &center,
  const float32 radius,
  const b2Vec2 &axis,
  const b2Color &color
) {
  DrawPoint(center, radius, color);
  DrawSegment(center, center + radius * axis, detail::brighten(color));
}

void B2::DebugDrawNanoVG::DrawSegment(
  const b2Vec2 &p1,
  const b2Vec2 &p2,
  const b2Color &color
) {
  if (ctx) {
    nvgBeginPath(ctx);
    nvgStrokeColor(ctx, detail::castColor(color));
    nvgStrokeWidth(ctx, strokeWidth);
    nvgMoveTo(ctx, p1.x, p1.y);
    nvgLineTo(ctx, p2.x, p2.y);
    nvgStroke(ctx);
  }
}

void B2::DebugDrawNanoVG::DrawTransform(const b2Transform &transform) {
  static const float AXIS_SCALE = 0.4f;
  static const b2Color X_AXIS = {1.0f, 0.0f, 0.0f};
  static const b2Color Y_AXIS = {0.0f, 1.0f, 0.0f};

  const b2Vec2 origin = transform.p;
  
  DrawSegment(origin, origin + AXIS_SCALE * transform.q.GetXAxis(), X_AXIS);
  DrawSegment(origin, origin + AXIS_SCALE * transform.q.GetYAxis(), Y_AXIS);
}

void B2::DebugDrawNanoVG::DrawPoint(
  const b2Vec2 &p,
  const float32 size,
  const b2Color &color
) {
  if (ctx) {
    nvgBeginPath(ctx);
    nvgFillColor(ctx, detail::castColor(color));
    nvgCircle(ctx, p.x, p.y, size);
    nvgFill(ctx);
  }
}

void B2::DebugDrawNanoVG::setContext(NVGcontext *const newCtx) {
  ctx = newCtx;
}
