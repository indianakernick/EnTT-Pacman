//
//  filter surface.inl
//  Simpleton Engine
//
//  Created by Indi Kernick on 2/5/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#include <cassert>

template <uint32_t BPP, typename Function>
void G2D::filterInplace(G2D::Surface &surface, Function &&filter) {
  assert(surface.bytesPerPixel() == BPP);

  const ptrdiff_t pitch = surface.pitch();
  const ptrdiff_t width = surface.widthBytes();
  const ptrdiff_t betweenRow = pitch - width;
  uint8_t* data = surface.data();
  uint8_t* const dataEnd = surface.dataEnd();
  
  while (data != dataEnd) {
    for (uint8_t *const rowEnd = data + width; data != rowEnd; data += BPP) {
      std::array<uint8_t, BPP> pixel;
      std::memcpy(pixel.data(), data, BPP);
      pixel = filter(pixel);
      std::memcpy(data, pixel.data(), BPP);
    }
    data += betweenRow;
  }
}

template <uint32_t DST_BPP, uint32_t SRC_BPP, typename Function>
void G2D::filterCopy(G2D::Surface &dst, const G2D::Surface &src, Function &&filter) {
  assert(dst.bytesPerPixel() == DST_BPP);
  assert(src.bytesPerPixel() == SRC_BPP);
  assert(dst.width() == src.width());
  assert(dst.height() == src.height());

  const ptrdiff_t dstPitch = dst.pitch();
  const ptrdiff_t dstWidth = dst.widthBytes();
  const ptrdiff_t dstBetweenRow = dstPitch - dstWidth;
  const ptrdiff_t srcBetweenRow = src.pitch() - src.widthBytes();
  uint8_t* dstData = dst.data();
  uint8_t* const dstDataEnd = dst.dataEnd();
  const uint8_t *srcData = src.data();
  
  while (dstData != dstDataEnd) {
    uint8_t *const rowEnd = dstData + dstWidth;
    for (; dstData != rowEnd; dstData += DST_BPP, srcData += SRC_BPP) {
      std::array<uint8_t, SRC_BPP> srcpixel;
      std::memcpy(srcpixel.data(), srcData, SRC_BPP);
      const std::array<uint8_t, DST_BPP> dstpixel = filter(srcpixel);
      std::memcpy(dstData, dstpixel.data(), DST_BPP);
    }
    dstData += dstBetweenRow;
    srcData += srcBetweenRow;
  }
}
