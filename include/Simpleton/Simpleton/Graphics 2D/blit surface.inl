//
//  blit surface.inl
//  Simpleton Engine
//
//  Created by Indi Kernick on 27/12/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

inline const char *G2D::FormatError::what() const noexcept {
  return "Cannot blit surfaces with different bytesPerPixel";
}

inline void G2D::blit(Surface &dst, const Surface &src) {
  blit(dst, src, 0, 0);
}

inline void G2D::blit(
  Surface &dst,
  const Surface &src,
  const Surface::Size srcX,
  const Surface::Size srcY
) {
  if (dst.bytesPerPixel() != src.bytesPerPixel()) {
    throw FormatError();
  }

  const ptrdiff_t dstPitch = dst.pitch();
  const ptrdiff_t srcPitch = src.pitch();
  const size_t width = src.widthBytes();
  uint8_t *dstRow = dst.data(srcX, srcY);
  const uint8_t *srcRow = src.data();
  const uint8_t *const srcEnd = src.dataEnd();
  
  // assumes the src surface lies completly within the dst surface
  // should probably assert this and write another function that handles it
  // at the cost of being slightly slower
  while (srcRow != srcEnd) {
    std::memcpy(dstRow, srcRow, width);
    dstRow += dstPitch;
    srcRow += srcPitch;
  }
}
