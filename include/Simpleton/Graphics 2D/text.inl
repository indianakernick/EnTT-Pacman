//
//  text.inl
//  Simpleton Engine
//
//  Created by Indi Kernick on 17/6/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#include <sstream>

inline G2D::Text::Text(G2D::Section &section)
  : section_{&section} {}

inline void G2D::Text::section(G2D::Section &section) {
  section_ = &section;
}

inline G2D::Section &G2D::Text::section() const {
  assert(section_);
  return *section_;
}

inline void G2D::Text::glyphSize(const glm::vec2 newSize) {
  glyphSize_ = newSize;
}

inline void G2D::Text::advance(const glm::vec2 newAdvance) {
  advance_ = newAdvance;
}

inline void G2D::Text::scale(const float newScale) {
  scale_ = newScale;
}

inline void G2D::Text::depth(const float newDepth) {
  depth_ = newDepth;
}

template <typename Enum>
void G2D::Text::depth(const Enum depth) {
  depth_ = G2D::depth(depth);
}

inline void G2D::Text::color(const glm::vec4 color) {
  color_ = color;
}

namespace G2D::detail {
  inline bool advanceChar(glm::vec2 &pos, const glm::vec2 advance, const char c) {
    switch (c) {
      case '\n':
        pos.x = 0.0f;
        pos.y += advance.y;
        return true;
      case ' ':
        pos.x += advance.x;
        break;
      case '\b':
        pos.x -= advance.x;
        break;
      case '\t': {
        const int chars = std::nearbyint(pos.x / advance.x);
        pos.x += advance.x * (8 - chars % 8);
        break;
      }
      case '\v':
        pos.y += advance.y;
        break;
      case '\r':
        pos.x = 0.0f;
        return true;
      default:
        if (' ' <= c && c <= '~') {
          pos.x += advance.x;
        }
    }
    return false;
  }

  template <Align ALIGN>
  constexpr float getAlign() {
    if constexpr (ALIGN == Align::LEFT) {
      return 0.0f;
    } else if constexpr (ALIGN == Align::CENTER) {
      return 0.5f;
    } else if constexpr (ALIGN == Align::RIGHT) {
      return 1.0f;
    }
  }
}

template <G2D::Align ALIGN, G2D::PlusXY PLUS_XY>
glm::vec2 G2D::Text::write(const glm::vec2 origin, const std::string_view str) {
  if constexpr (ALIGN == Align::LEFT) {
    return writeLeftImpl<PLUS_XY>(origin, str);
  }
  
  glm::vec2 beginPos = {0.0f, 0.0f};
  glm::vec2 endPos = beginPos;
  glm::vec2 alignedOrigin;
  const glm::vec2 scaledSize = scale_ * glyphSize_;
  const glm::vec2 scaledAdv = scale_ * advance_;
  const char *const endChar = str.data() + str.size();
  const char *rowBegin = str.data();
  const char *rowEnd = rowBegin;

  for ( ; rowEnd != str.data() + str.size() + 1; ++rowEnd) {
    const float width = endPos.x;
    if (rowEnd != endChar && !detail::advanceChar(endPos, scaledAdv, *rowEnd)) {
      continue;
    }
    
    alignedOrigin = {
      origin.x - (width - scaledAdv.x + scaledSize.x) * detail::getAlign<ALIGN>(),
      origin.y
    };

    for (; rowBegin != rowEnd; ++rowBegin) {
      const char c = *rowBegin;
      writeChar<PLUS_XY>(alignedOrigin + beginPos, scaledSize, c);
      detail::advanceChar(beginPos, scaledAdv, c);
    }
    ++rowBegin;
    beginPos = endPos;
  }
  
  return alignedOrigin + endPos;
}

template <G2D::Align ALIGN, G2D::PlusXY PLUS_XY>
glm::vec2 G2D::Text::write(const glm::vec2 origin, const char c) {
  const glm::vec2 scaledSize = scale_ * glyphSize_;
  const glm::vec2 alignedOrigin = {
    origin.x - scaledSize.x * detail::getAlign<ALIGN>(),
    origin.y
  };
  writeChar<PLUS_XY>(alignedOrigin, scaledSize, c);
  glm::vec2 pos = {0.0f, 0.0f};
  detail::advanceChar(pos, scale_ * advance_, c);
  return alignedOrigin + pos;
}

template <G2D::Align ALIGN, G2D::PlusXY PLUS_XY, typename T>
G2D::Text::EnableNotStr<T, glm::vec2> G2D::Text::write(
  const glm::vec2 origin,
  const T &thing
) {
  // @TODO maybe a custom stream_buf?
  std::stringstream stream;
  stream << thing;
  if (stream.good()) {
    return write<ALIGN, PLUS_XY>(origin, stream.str());
  } else {
    return origin;
  }
}

template <G2D::PlusXY PLUS_XY>
glm::vec2 G2D::Text::writeLeftImpl(const glm::vec2 origin, const std::string_view str) {
  glm::vec2 pos = {0.0f, 0.0f};
  const glm::vec2 scaledSize = scale_ * glyphSize_;
  const glm::vec2 scaleAdv = scale_ * advance_;
  
  for (const char c : str) {
    writeChar<PLUS_XY>(origin + pos, scaledSize, c);
    detail::advanceChar(pos, scaleAdv, c);
  }

  return origin + pos;
}

template <G2D::PlusXY PLUS_XY>
void G2D::Text::writeChar(const glm::vec2 pos, const glm::vec2 size, const char c) {
  if ('!' <= c && c <= '~') {
    section_->quad();
    section_->depth(depth_);
    section_->tilePos(pos, size);
    section_->tileTex<PLUS_XY>(Sprite::ID(c - '!'));
    section_->color(color_);
  }
}
