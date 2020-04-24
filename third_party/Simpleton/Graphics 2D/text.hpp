//
//  text.hpp
//  Simpleton Engine
//
//  Created by Indi Kernick on 17/6/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#ifndef engine_graphics_2d_text_hpp
#define engine_graphics_2d_text_hpp

#include <string_view>
#include <type_traits>
#include "quad writer.hpp"

namespace G2D {
  /// Text alignment
  enum class Align {
    LEFT,
    CENTER,
    RIGHT
  };

  class Text {
  
    template <typename T, typename Ret>
    using EnableNotStr = std::enable_if_t<
      !std::is_convertible_v<T, std::string_view>,
      Ret
    >;

  public:
    Text() = default;
    explicit Text(Section &);
    
    /// Set the section that glyphs will be written to. A pointer to the section
    /// is stored interally.
    void section(Section &);
    /// Get a refernce to the section that is currently being written to.
    Section &section() const;
    
    /// Set the size (in camera coordinates) of a glyph at a scale of 1.0
    void glyphSize(glm::vec2);
    /// Set the advance distance (in camera coordinates) for advancing to the
    /// next character or next line. This class only supports monospaced text
    void advance(glm::vec2);
    /// Set the scale relative to the glyph size that the glyphs will be
    /// written. If scale is 2.0f then glyphs will be written at a size of
    /// glyphSize * 2.0f
    void scale(float);
    /// Set the depth of the text using a float
    void depth(float);
    /// Set the depth of the text using a depth enum
    template <typename Enum>
    void depth(Enum);
    /// Set the color of the text
    void color(glm::vec4);
    
    /// Write a string of characters at a position and return the position of
    /// the next character
    template <Align ALIGN, PlusXY PLUS_XY>
    glm::vec2 write(glm::vec2, std::string_view);
    /// Write a single character at a position and return the position of the
    /// next character
    template <Align ALIGN, PlusXY PLUS_XY>
    glm::vec2 write(glm::vec2, char);
    /// Write a serializable object at a position and return the position of the
    /// next character. The type must have an overloaded operator<<
    template <Align ALIGN, PlusXY PLUS_XY, typename T>
    EnableNotStr<T, glm::vec2> write(glm::vec2, const T &);
    
    #define WRAPPER(NAME, ALIGN)                                                \
      template <PlusXY PLUS_XY = PlusXY::RIGHT_DOWN, typename Value>            \
      glm::vec2 write##NAME(const glm::vec2 pos, Value &&value) {               \
        return write<Align::ALIGN, PLUS_XY>(pos, std::forward<Value>(value));   \
      }
    WRAPPER(Left, LEFT)
    WRAPPER(Center, CENTER)
    WRAPPER(Right, RIGHT)
    #undef WRAPPER
    
  private:
    Section *section_ {};
    glm::vec4 color_ {1.0f};
    glm::vec2 glyphSize_ {1.0f};
    glm::vec2 advance_ {1.0f};
    float scale_ {1.0f};
    float depth_ {0.0f};

    template <PlusXY PLUS_XY>
    glm::vec2 writeLeftImpl(glm::vec2, std::string_view);
    template <PlusXY PLUS_XY>
    void writeChar(glm::vec2, glm::vec2, char);
  };
}

#include "text.inl"

#endif
