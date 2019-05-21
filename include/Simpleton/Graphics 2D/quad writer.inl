//
//  quad writer.inl
//  Simpleton Engine
//
//  Created by Indi Kernick on 22/4/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#include <algorithm>
#include <glm/gtc/constants.hpp>

inline G2D::Section::Section(const RenderParams &params, const Sprite::Sheet &sheet)
  : renderParams{params}, spriteSheet{sheet} {
  quads.reserve(512);
}

inline const G2D::RenderParams &G2D::Section::params() const {
  return renderParams;
}

inline const Sprite::Sheet &G2D::Section::sheet() const {
  return spriteSheet;
}

inline void G2D::Section::clear() {
  quads.clear();
}

inline void G2D::Section::reserveQuads(const size_t size) {
  quads.reserve(quads.size() + size);
}

template <typename Function>
void G2D::Section::sort(Function &&function) {
  std::sort(
    quads.begin(),
    quads.end(),
    function
  );
}

inline G2D::Quad &G2D::Section::quad() {
  return quads.emplace_back();
}

inline G2D::Quad &G2D::Section::dup() {
  assert(!quads.empty());
  return quads.emplace_back(quads.back());
}

inline void G2D::Section::depth(const float depth) {
  assert(!quads.empty());
  Quad &quad = quads.back();
  quad[0].pos.z =
  quad[1].pos.z =
  quad[2].pos.z =
  quad[3].pos.z = depth;
}

template <typename Enum>
void G2D::Section::depth(const Enum e) {
  depth(G2D::depth(e));
}

namespace G2D::detail {
  inline void setPos(glm::vec3 &dst, const glm::vec2 src) {
    dst.x = src.x;
    dst.y = src.y;
  }
}

inline void G2D::Section::dupPos() {
  assert(quads.size() > 1);
  Quad &quad = quads.back();
  const Quad &prev = *(quads.cend() - 2);
  for (size_t i = 0; i != 4; ++i) {
    detail::setPos(quad[i].pos, prev[i].pos);
  }
}

inline void G2D::Section::dupPosDepth() {
  assert(quads.size() > 1);
  Quad &quad = quads.back();
  const Quad &prev = *(quads.cend() - 2);
  for (size_t i = 0; i != 4; ++i) {
    quad[i].pos = prev[i].pos;
  }
}

inline void G2D::Section::tilePos(
  const glm::vec2 pos,
  const glm::vec2 size
) {
  assert(!quads.empty());
  Quad &quad = quads.back();
  detail::setPos(quad[0].pos, pos);
  detail::setPos(quad[1].pos, {pos.x + size.x, pos.y});
  detail::setPos(quad[2].pos, pos + size);
  detail::setPos(quad[3].pos, {pos.x, pos.y + size.y});
}

inline void G2D::Section::rotTilePos(
  const float angle,
  const glm::vec2 pos,
  const glm::vec2 size
) {
  assert(!quads.empty());

  const glm::vec2 halfSize = size * 0.5f;
  const glm::vec2 topRight = glm::vec2(
    std::cos(angle + glm::quarter_pi<float>()),
    std::sin(angle + glm::quarter_pi<float>())
  ) * halfSize * glm::root_two<float>();
  const glm::vec2 topLeft = {-topRight.y, topRight.x};
  const glm::vec2 botLeft = -topRight;
  const glm::vec2 botRight = -topLeft;
  const glm::vec2 shift = pos + halfSize;
  
  Quad &quad = quads.back();
  detail::setPos(quad[0].pos, botLeft + shift);
  detail::setPos(quad[1].pos, botRight + shift);
  detail::setPos(quad[2].pos, topRight + shift);
  detail::setPos(quad[3].pos, topLeft + shift);
}

template <G2D::Origin ORIGIN>
void G2D::Section::rotTilePos(
  const float angle,
  const glm::vec2 pos,
  const glm::vec2 size
) {
  assert(!quads.empty());

  const glm::vec2 ORIGIN_POS[9] = {
    {0.5f, -0.5f}, {0.0f, -0.5f}, {-0.5f, -0.5f}, {-0.5f, 0.0f},
    {-0.5f, 0.5f}, {0.0f, 0.5f}, {0.5f, 0.5f}, {0.5f, 0.0f},
    {0.0f, 0.0f}
  };
  const glm::vec2 originPos = ORIGIN_POS[static_cast<size_t>(ORIGIN)];
  
  const glm::vec2 origin = originPos * size;
  const float c = std::cos(angle);
  const float s = std::sin(angle);
  const glm::mat2 rot = {
    {c, s},
    {-s, c}
  };
  
  const glm::vec2 halfSize = size * 0.5f;
  const glm::vec2 tr = halfSize;
  const glm::vec2 bl = -halfSize;
  const glm::vec2 tl = {bl.x, tr.y};
  const glm::vec2 br = {tr.x, bl.y};
  
  Quad &quad = quads.back();
  detail::setPos(quad[0].pos, pos + rot * (bl + origin));
  detail::setPos(quad[1].pos, pos + rot * (br + origin));
  detail::setPos(quad[2].pos, pos + rot * (tr + origin));
  detail::setPos(quad[3].pos, pos + rot * (tl + origin));
}

inline void G2D::Section::linePos(
  const glm::vec2 start,
  const glm::vec2 end,
  const float thickness
) {
  const float angle = std::atan2(end.y - start.y, end.x - start.x);
  const float halfThickness = thickness * 0.5f;
  const float xOff = std::cos(angle - glm::half_pi<float>());
  const float yOff = std::sin(angle - glm::half_pi<float>());
  const glm::vec2 bottom = glm::vec2(xOff, yOff) * halfThickness;
  const glm::vec2 top = glm::vec2(-xOff, -yOff) * halfThickness;
  
  Quad &quad = quads.back();
  detail::setPos(quad[0].pos, start + bottom);
  detail::setPos(quad[1].pos, end + bottom);
  detail::setPos(quad[2].pos, end + top);
  detail::setPos(quad[3].pos, start + top);
}

inline void G2D::Section::dupTex() {
  assert(quads.size() > 1);
  Quad &quad = quads.back();
  const Quad &prev = *(quads.cend() - 2);
  for (size_t i = 0; i != 4; ++i) {
    quad[i].texCoord = prev[i].texCoord;
  }
}

template <G2D::PlusXY PLUS_XY>
void G2D::Section::tileTex(const glm::vec2 min, const glm::vec2 max) {
  assert(!quads.empty());
  
  constexpr size_t Is[4][4] = {
                  // +x      +y
    {0, 1, 2, 3}, // right   up
    {1, 0, 3, 2}, // left    up
    {3, 2, 1, 0}, // right   down
    {2, 3, 0, 1}  // left    down
  };
  constexpr size_t i = static_cast<size_t>(PLUS_XY);
  
  Quad &quad = quads.back();
  quad[Is[i][0]].texCoord = min;
  quad[Is[i][1]].texCoord = {max.x, min.y};
  quad[Is[i][2]].texCoord = max;
  quad[Is[i][3]].texCoord = {min.x, max.y};
}

template <G2D::PlusXY PLUS_XY>
void G2D::Section::tileTex(const Math::RectPP<float> coords) {
  tileTex<PLUS_XY>(coords.min, coords.max);
}

template <G2D::PlusXY PLUS_XY>
void G2D::Section::tileTex(const Sprite::ID sprite) {
  tileTex<PLUS_XY>(spriteSheet.getSprite(sprite));
}

template <G2D::PlusXY PLUS_XY>
void G2D::Section::tileTex(const std::string_view name) {
  tileTex<PLUS_XY>(spriteSheet.getIDfromName(name));
}

inline void G2D::Section::whitepixel() {
  assert(!quads.empty());
  const glm::vec2 whitepixel = spriteSheet.getWhitepixel();
  assert(whitepixel != Sprite::no_whitepixel);
  
  Quad &quad = quads.back();
  quad[0].texCoord =
  quad[1].texCoord =
  quad[2].texCoord = 
  quad[3].texCoord = whitepixel;
}

inline void G2D::Section::color(const glm::vec4 color) {
  assert(!quads.empty());
  
  Quad &quad = quads.back();
  quad[0].color =
  quad[1].color =
  quad[2].color =
  quad[3].color = color;
}

inline void G2D::Section::colorWhite() {
  color({1.0f, 1.0f, 1.0f, 1.0f});
}

inline void G2D::Section::xGradient(const glm::vec4 low, const glm::vec4 high) {
  assert(!quads.empty());
  
  Quad &quad = quads.back();
  quad[0].color = low;
  quad[1].color = high;
  quad[2].color = high;
  quad[3].color = low;
}

inline void G2D::Section::yGradient(const glm::vec4 low, const glm::vec4 high) {
  assert(!quads.empty());
  
  Quad &quad = quads.back();
  quad[0].color = low;
  quad[1].color = low;
  quad[2].color = high;
  quad[3].color = high;
}

inline void G2D::Section::render(Renderer &renderer) const {
  const QuadRange range {0, quads.size()};
  renderer.writeQuads(range, quads.data());
  renderer.render(range, renderParams);
}

inline G2D::QuadWriter::QuadWriter() {
  sections.reserve(64);
}

inline void G2D::QuadWriter::clear() {
  sections.clear();
}

inline void G2D::QuadWriter::clearQuads() {
  for (Section &section : sections) {
    section.clear();
  }
}

inline G2D::Section &G2D::QuadWriter::section(
  const glm::mat3 &cam,
  const SheetTex &sheetTex
) {
  const RenderParams params {cam, sheetTex.tex()};
  for (auto s = sections.begin(); s != sections.end(); ++s) {
    if (s->params() == params) {
      return *s;
    }
  }
  return sections.emplace_back(params, sheetTex.sheet());
}

inline void G2D::QuadWriter::render(Renderer &renderer) const {
  for (const Section &section : sections) {
    section.render(renderer);
  }
}
