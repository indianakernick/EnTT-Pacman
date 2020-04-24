//
//  renderer.hpp
//  Simpleton Engine
//
//  Created by Indi Kernick on 11/2/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#ifndef engine_graphics_2d_renderer_hpp
#define engine_graphics_2d_renderer_hpp

#include <vector>
#include "types.hpp"
#include "surface.hpp"
#include <string_view>
#include "../OpenGL/buffer.hpp"
#include "../OpenGL/texture.hpp"
#include "../OpenGL/vertex array.hpp"
#include "../OpenGL/shader program.hpp"

namespace G2D {
  class Renderer {
  public:
    Renderer() = default;
  
    void init();
    void quit();
    
    TextureID addTexture(GL::Texture2D &&);
    TextureID addTexture(const Surface &, TexParams);
    TextureID addTexture(std::string_view, TexParams);
    
    /// Increase the size of the GPU quad buffer and return true if the size
    /// was actually increased. Increasing the size will clear the memory.
    bool resizeQuadBuf(size_t);
    /// Copy quads from CPU memory to GPU memory. Returns true if the GPU memory
    /// had to be resized. If the GPU buffer had to be resized, it's contents
    /// will be cleared but only the given quads will be copied.
    bool writeQuads(QuadRange, const Quad *);
    /// Render the quads in GPU memory with the given rendering parameters
    void render(QuadRange, const RenderParams &);
  
  private:
    std::vector<GL::Texture2D> textures;
    std::vector<ElemType> indicies;
    size_t numQuads = 0;
    GL::ArrayBuffer arrayBuf;
    GL::ElementBuffer elemBuf;
    GL::VertexArray vertArray;
    GL::ShaderProgram program;
    GLint viewProjLoc;
    GLint texLoc;
    
    void initState();
    void initUniforms();
    void initVertexArray();
    void fillIndicies(size_t);
    void setQuadBufSize(size_t);
    template <size_t SIZE>
    void initImpl(const char (&)[SIZE]);
  };
}

#include "renderer.inl"

#endif
