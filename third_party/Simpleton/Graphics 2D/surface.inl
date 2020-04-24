//
//  surface.inl
//  Simpleton Engine
//
//  Created by Indi Kernick on 27/12/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "../Memory/alloc.hpp"

inline G2D::Surface::Surface()
  : mData(nullptr),
    mPitch(0),
    mWidth(0),
    mHeight(0),
    mBytesPerPixel(0) {}

inline G2D::Surface::Surface(const Size width, const Size height, const BytesPerPixel bpp)
  : mData(static_cast<Surface::Byte *>(Memory::alloc(width * height * bpp))),
    mPitch(width * bpp),
    mWidth(width),
    mHeight(height),
    mBytesPerPixel(bpp) {}

inline G2D::Surface::Surface(const Size width, const Size height, const BytesPerPixel bpp, const Byte byte)
  : Surface(width, height, bpp) {
  std::memset(mData.get(), byte, height * mPitch);
}

inline G2D::Surface::Surface(
  const Size width,
  const Size height,
  const BytesPerPixel bpp,
  const Pitch pitch,
  Byte *const data
) : mData(data),
    mPitch(pitch),
    mWidth(width),
    mHeight(height),
    mBytesPerPixel(bpp) {}

inline G2D::Surface::Byte *G2D::Surface::data() {
  return mData.get();
}

inline G2D::Surface::Byte *G2D::Surface::data(const Size x, const Size y) {
  return mData.get() + (y * mPitch + x * mBytesPerPixel);
}

inline G2D::Surface::Byte *G2D::Surface::dataEnd() {
  return mData.get() + (static_cast<Pitch>(mHeight) * mPitch);
}

inline const G2D::Surface::Byte *G2D::Surface::data() const {
  return mData.get();
}

inline const G2D::Surface::Byte *G2D::Surface::data(const Size x, const Size y) const {
  return mData.get() + (y * mPitch + x * mBytesPerPixel);
}

inline const G2D::Surface::Byte *G2D::Surface::dataEnd() const {
  return mData.get() + (static_cast<Pitch>(mHeight) * mPitch);
}

inline size_t G2D::Surface::size() const {
  return std::abs(static_cast<Pitch>(mHeight) * mPitch);
}

inline G2D::Surface::Pitch G2D::Surface::pitch() const {
  return mPitch;
}

inline G2D::Surface::Size G2D::Surface::padding() const {
  return mPitch - widthBytes();
}

inline G2D::Surface::Size G2D::Surface::width() const {
  return mWidth;
}

inline G2D::Surface::Size G2D::Surface::widthBytes() const {
  return mWidth * mBytesPerPixel;
}

inline G2D::Surface::Size G2D::Surface::height() const {
  return mHeight;
}

inline G2D::Surface::BytesPerPixel G2D::Surface::bytesPerPixel() const {
  return mBytesPerPixel;
}
