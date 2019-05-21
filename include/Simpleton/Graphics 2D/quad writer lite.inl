//
//  quad writer lite.inl
//  Simpleton Engine
//
//  Created by Indi Kernick on 9/6/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

inline G2D::QuadWriterLite::QuadWriterLite() {
  quads.reserve(2048);
  sections.reserve(64);
  params.reserve(64);
}

inline void G2D::QuadWriterLite::clear() {
  quads.clear();
  sections.clear();
  params.clear();
}

inline void G2D::QuadWriterLite::section(const RenderParams &param) {
  sections.push_back(quads.size());
  params.push_back(param);
}

inline void G2D::QuadWriterLite::reserveQuads(const size_t size) {
  quads.reserve(quads.size() + size);
}

inline const G2D::RenderParams &G2D::QuadWriterLite::sectionParams() const {
  assert(params.size());
  return params.back();
}

template <typename Function>
void G2D::QuadWriterLite::sort(Function &&function) {
  assert(sections.size());
  
  std::sort(
    quads.data() + sections.back(),
    quads.data() + quads.size(),
    function
  );
}

inline G2D::Quad &G2D::QuadWriterLite::quad() {
  assert(sections.size());
  return quads.emplace_back();
}

inline void G2D::QuadWriterLite::depth(const float depth) {
  assert(quads.size() && sections.size());
  
  Quad &quad = quads.back();
  quad[0].pos.z =
  quad[1].pos.z =
  quad[2].pos.z =
  quad[3].pos.z = depth;
}

template <typename Enum>
void G2D::QuadWriterLite::depth(const Enum e) {
  depth(G2D::depth(e));
}

namespace G2D::detail {
  inline void setPosL(glm::vec3 &dst, const glm::vec2 src) {
    dst.x = src.x;
    dst.y = src.y;
  }
}

inline void G2D::QuadWriterLite::tilePos(
  const glm::vec2 pos,
  const glm::vec2 size
) {
  assert(quads.size() && sections.size());
  
  Quad &quad = quads.back();
  detail::setPosL(quad[0].pos, pos);
  detail::setPosL(quad[1].pos, {pos.x + size.x, pos.y});
  detail::setPosL(quad[2].pos, pos + size);
  detail::setPosL(quad[3].pos, {pos.x, pos.y + size.y});
}

template <G2D::PlusXY PLUS_XY>
void G2D::QuadWriterLite::tileTex(const glm::vec2 min, const glm::vec2 max) {
  assert(quads.size() && sections.size());
  
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
void G2D::QuadWriterLite::tileTex(const Math::RectPP<float> coords) {
  tileTex<PLUS_XY>(coords.min, coords.max);
}

inline void G2D::QuadWriterLite::color(const glm::vec4 color) {
  assert(quads.size() && sections.size());
  
  Quad &quad = quads.back();
  quad[0].color =
  quad[1].color =
  quad[2].color =
  quad[3].color = color;
}

inline void G2D::QuadWriterLite::colorWhite() {
  color({1.0f, 1.0f, 1.0f, 1.0f});
}

inline void G2D::QuadWriterLite::append(const QuadWriterLite &writer) {
  const size_t numQuads = quads.size();
  quads.insert(quads.end(), writer.quads.cbegin(), writer.quads.cend());
  for (const size_t section : writer.sections) {
    sections.push_back(numQuads + section);
  }
  params.insert(params.end(), writer.params.cbegin(), writer.params.cend());
}

inline void G2D::QuadWriterLite::render(Renderer &renderer) const {
  renderer.writeQuads({0, quads.size()}, quads.data());
  if (sections.empty()) {
    return;
  }
  QuadRange range;
  range.begin = sections[0];
  for (size_t s = 1; s != sections.size(); ++s) {
    range.end = sections[s];
    renderer.render(range, params[s - 1]);
    range.begin = range.end;
  }
  range.end = quads.size();
  renderer.render(range, params.back());
}
