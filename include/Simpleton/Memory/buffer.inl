//
//  buffer.inl
//  Simpleton Engine
//
//  Created by Indi Kernick on 25/09/2016.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#include <cassert>
#include <utility>

inline Memory::Buffer::Buffer(const size_t size) noexcept
  : mData{allocBytes(size)}, mSize{size} {}

inline Memory::Buffer::Buffer(const size_t size, const std::byte byte) noexcept
  : Buffer{size} {
  fill(byte);
}

inline Memory::Buffer::Buffer(Buffer &&other) noexcept
  : mData{std::exchange(other.mData, nullptr)},
    mSize{std::exchange(other.mSize, 0)} {}

inline Memory::Buffer &Memory::Buffer::operator=(Buffer &&other) noexcept {
  dealloc(mData);
  mData = std::exchange(other.mData, nullptr);
  mSize = std::exchange(other.mSize, 0);
  return *this;
}

inline Memory::Buffer::~Buffer() noexcept {
  dealloc(mData);
}

inline bool Memory::Buffer::operator==(const Buffer &other) const noexcept {
  assert(mData);
  return mSize == other.mSize && std::memcmp(mData, other.mData, mSize) == 0;
}

inline bool Memory::Buffer::operator!=(const Buffer &other) const noexcept {
  return !(*this == other);
}

inline bool Memory::Buffer::operator<(const Buffer &other) const noexcept {
  assert(mData);
  if (mSize == other.mSize) {
    return std::memcmp(mData, other.mData, mSize) < 0;
  } else {
    return mSize < other.mSize;
  }
}

inline bool Memory::Buffer::operator>(const Buffer &other) const noexcept {
  return other < *this;
}

inline bool Memory::Buffer::operator<=(const Buffer &other) const noexcept {
  return !(other < *this);
}

inline bool Memory::Buffer::operator>=(const Buffer &other) const noexcept {
  return !(*this < other);
}

inline void Memory::Buffer::swap(Buffer &other) noexcept {
  std::swap(mData, other.mData);
  std::swap(mSize, other.mSize);
}

inline void Memory::Buffer::copyFrom(const Buffer &buffer) noexcept {
  assert(mData);
  std::memcpy(mData, buffer.mData, std::min(mSize, buffer.mSize));
}

inline void Memory::Buffer::copyFrom(const Buffer &buffer, const std::byte byte) noexcept {
  copyFrom(buffer);
  if (mSize > buffer.mSize) {
    fillLast(mSize - buffer.mSize, byte);
  }
}

inline Memory::Buffer Memory::Buffer::dup() const noexcept {
  return dup(mSize);
}

inline Memory::Buffer Memory::Buffer::dup(const size_t size) const noexcept {
  Buffer buf{size};
  buf.copyFrom(*this);
  return buf;
}

inline Memory::Buffer Memory::Buffer::dup(const size_t size, const std::byte byte) const noexcept {
  Buffer buf{size};
  buf.copyFrom(*this, byte);
  return buf;
}

inline void Memory::Buffer::zero() noexcept {
  fill(std::byte{});
}

inline void Memory::Buffer::fill(const std::byte byte) noexcept {
  fillFirst(mSize, byte);
}

inline void Memory::Buffer::fillFirst(const size_t size, const std::byte byte) noexcept {
  assert(mData);
  assert(size <= mSize);
  std::memset(mData, static_cast<int>(byte), size);
}

inline void Memory::Buffer::fillLast(const size_t size, const std::byte byte) noexcept {
  assert(mData);
  assert(size <= mSize);
  std::memset(mData + (mSize - size), static_cast<int>(byte), size);
}

inline std::byte *Memory::Buffer::findPtr(const std::byte byte) noexcept {
  return const_cast<std::byte *>(std::as_const(*this).findPtr(byte));
}

inline const std::byte *Memory::Buffer::findPtr(const std::byte byte) const noexcept {
  assert(mData);
  return reinterpret_cast<const std::byte *>(
    std::memchr(mData, static_cast<int>(byte), mSize)
  );
}

inline size_t Memory::Buffer::findIdx(const std::byte byte) const noexcept {
  const std::byte *const ptr = findPtr(byte);
  if (ptr == nullptr) {
    return ~size_t{};
  } else {
    return ptr - mData;
  }
}

inline void Memory::swap(Buffer &a, Buffer &b) noexcept {
  a.swap(b);
}
