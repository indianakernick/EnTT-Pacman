//
//  quad writer lite.hpp
//  Simpleton Engine
//
//  Created by Indi Kernick on 9/6/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#ifndef engine_graphics_2d_quad_writer_lite_hpp
#define engine_graphics_2d_quad_writer_lite_hpp

#include "depth.hpp"
#include "renderer.hpp"
#include "../Math/rect.hpp"

namespace G2D {
  class QuadWriterLite {
  public:
    QuadWriterLite();
    
    /// Remove all of the sections
    void clear();
    
    /// Start a new section with the given rendering parameters
    void section(const RenderParams &);
    /// Make space for the given number of quads to avoid further reallocations
    void reserveQuads(size_t);
    /// Get the RenderParams object associated with the current section
    const RenderParams &sectionParams() const;
    
    /// Sort the quads in the current section by the given sorting predicate
    template <typename Function>
    void sort(Function &&);
    
    /// Start a new quad and return it
    Quad &quad();
    
    /// Set the depth of the current quad
    void depth(float);
    /// Set the depth of the current quad using an enum
    template <typename Enum>
    void depth(Enum);
    
    /// Write positions of verticies on the current quad as an axis-aligned
    /// rectangle.
    void tilePos(glm::vec2, glm::vec2 = {1.0f, 1.0f});
    
    /// Write texture coordinates of vertices on the current quad assuming that
    /// the texture is sampled as an axis-aligned rectangle
    template <PlusXY PLUS_XY = PlusXY::RIGHT_UP>
    void tileTex(glm::vec2, glm::vec2);
    /// Write texture coordinates of vertices on the current quad assuming that
    /// the texture is sampled as an axis-aligned rectangle
    template <PlusXY PLUS_XY = PlusXY::RIGHT_UP>
    void tileTex(Math::RectPP<float>);
    
    /// Set the color of the current quad
    void color(glm::vec4);
    /// Set the color of the current quad to white
    void colorWhite();
    
    /// Append all sections from the given writer into this writer. Quads before
    /// the first section in the given writer become part of the current
    /// section in this writer.
    void append(const QuadWriterLite &);
    
    /// Copy the quads into GPU memory and issue an number of draw calls
    void render(Renderer &) const;
    
  private:
    std::vector<Quad> quads;
    // each section is an index to its first quad
    std::vector<size_t> sections;
    std::vector<RenderParams> params;
  };
}

#include "quad writer lite.inl"

#endif
