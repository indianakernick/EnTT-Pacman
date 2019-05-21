//
//  quad writer.hpp
//  Simpleton Engine
//
//  Created by Indi Kernick on 22/4/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#ifndef engine_graphics_2d_quad_writer_hpp
#define engine_graphics_2d_quad_writer_hpp

#include "depth.hpp"
#include "renderer.hpp"
#include "sheet tex.hpp"

namespace G2D {
  enum class Origin {
    TOP_LEFT,
    TOP_MID,
    TOP_RIGHT,
    MID_RIGHT,
    BOTTOM_RIGHT,
    BOTTOM_MID,
    BOTTOM_LEFT,
    MID_LEFT,
    CENTER
  };

  class Section {
  public:
    Section(Section &&) = default;
    Section &operator=(Section &&) = default;
    Section(const RenderParams &, const Sprite::Sheet &);
  
    /// Get the RenderParams object
    const RenderParams &params() const;
    /// Get the Sprite::Sheet object
    const Sprite::Sheet &sheet() const;
    /// Remove all quads
    void clear();
    /// Make space for additional quads
    void reserveQuads(size_t);
    /// Sort the quads by the given sorting predicate
    template <typename Function>
    void sort(Function &&);
  
    /// Create a new quad
    Quad &quad();
    /// Create a new quad that is a duplicate of the previous quad
    Quad &dup();
    
    /// Set the depth of the current quad
    void depth(float);
    /// Set the depth of the current quad using an enum
    template <typename Enum>
    void depth(Enum);
    
    /// Copy the positions of the verticies from the previous quad into the
    /// current quad
    void dupPos();
    /// Copy the positions of the verticies and the depth from the previous
    /// quad into the current quad
    void dupPosDepth();
    /// Write positions of verticies on the current quad as an axis-aligned
    /// rectangle.
    void tilePos(glm::vec2, glm::vec2 = {1.0f, 1.0f});
    /// Write positions of verticies on the current quad as a rectangle rotated
    /// around it's center. The quad is position relative to it's bottom left
    /// corner like tilePos.
    void rotTilePos(float, glm::vec2, glm::vec2 = {1.0f, 1.0f});
    /// Write positions of verticies on the current quad as a rectangle rotated
    /// around a given origin. The quad is positioned relative to the origin.
    /// This function isn't quite as fast as rotTilePos without an origin.
    template <Origin ORIGIN>
    void rotTilePos(float, glm::vec2, glm::vec2 = {1.0f, 1.0f});
    /// Write positions of verticies on the current quad as a line between two
    /// points
    void linePos(glm::vec2, glm::vec2, float = 1.0f);
    
    /// Copy the texture coordinates of the verticies on the previous quad onto
    /// the current quad
    void dupTex();
    /// Write texture coordinates of vertices on the current quad assuming that
    /// the texture is sampled as an axis-aligned rectangle
    template <PlusXY PLUS_XY = PlusXY::RIGHT_UP>
    void tileTex(glm::vec2, glm::vec2);
    /// Write texture coordinates of vertices on the current quad assuming that
    /// the texture is sampled as an axis-aligned rectangle
    template <PlusXY PLUS_XY = PlusXY::RIGHT_UP>
    void tileTex(Math::RectPP<float>);
    /// Write texture coordinates of vertices on the current quad assuming that
    /// the texture is sampled as an axis-aligned rectangle
    template <PlusXY PLUS_XY = PlusXY::RIGHT_UP>
    void tileTex(Sprite::ID);
    /// Write texture coordinates of vertices on the current quad assuming that
    /// the texture is sampled as an axis-aligned rectangle
    template <PlusXY PLUS_XY = PlusXY::RIGHT_UP>
    void tileTex(std::string_view);
    /// Set texture coordinates of vertices on the current quad to the
    /// whitepixel. Asserts if the sprite sheet doesn't have a whitepixel
    void whitepixel();
    
    /// Set the color of the current quad
    void color(glm::vec4);
    /// Set the color of the current quad to white
    void colorWhite();
    /// Set the colors of the verticies to create an x-gradient from low x
    /// to high x
    void xGradient(glm::vec4, glm::vec4);
    /// Set the colors of the verticies to create an y-gradient from low y
    /// to high y
    void yGradient(glm::vec4, glm::vec4);
    
    /// Copy the quads into GPU memory and issue a draw call
    void render(Renderer &) const;
    
  private:
    RenderParams renderParams;
    const Sprite::Sheet &spriteSheet;
    std::vector<Quad> quads;
  };

  class QuadWriter {
  public:
    QuadWriter();
    
    /// Remove all of the sections
    void clear();
    /// Clear quads on all sections
    void clearQuads();
    
    /// Create a new section with the given rendering params or get an existing
    /// section with the same params.
    Section &section(const glm::mat3 &, const SheetTex &);
    
    /// Render all of the sections
    void render(Renderer &) const;
    
  private:
    std::vector<Section> sections;
  };
}

#include "quad writer.inl"

#endif
