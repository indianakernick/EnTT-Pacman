//
//  sheet tex.inl
//  Simpleton Engine
//
//  Created by Indi Kernick on 2/5/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#include "../SDL/paths.hpp"

inline G2D::SheetTex::SheetTex(Sprite::Sheet &&sheet, const TextureID tex)
  : sheet_{std::move(sheet)}, tex_{tex} {}

inline void G2D::SheetTex::load(
  Renderer &renderer,
  const std::string &name,
  const TexParams params
) {
  const std::string path = SDL::res(name);
  tex_ = renderer.addTexture(path + ".png", params);
  sheet_ = Sprite::makeSheet(path + ".atlas");
}

inline void G2D::SheetTex::load(
  Renderer &renderer,
  const std::string &name,
  const MagFilter filter
) {
  TexParams params;
  params.wrap = TexWrap::CLAMP;
  params.min = static_cast<MinFilter>(filter);
  params.mag = filter;
  load(renderer, name, params);
}

inline const Sprite::Sheet &G2D::SheetTex::sheet() const {
  return sheet_;
}

inline G2D::TextureID G2D::SheetTex::tex() const {
  return tex_;
}
