//
//  buffer.inl
//  Simpleton Engine
//
//  Created by Indi Kernick on 25/09/2016.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

inline Memory::Buffer::Buffer(const size_t size)
  : mData{allocBytes(size)}, mSize{size} {}

inline Memory::Buffer::Buffer(const size_t size, Zero)
  : mData{allocBytes(size)}, mSize{size} {
  std::memset(data(), 0, mSize);
}

inline Memory::Buffer::Buffer(const size_t size, One)
  : mData{allocBytes(size)}, mSize{size} {
  std::memset(data(), static_cast<int>(~std::byte{}), mSize);
}

inline Memory::Buffer::Buffer(const size_t size, const std::byte byte)
  : mData{allocBytes(size)}, mSize{size} {
  std::memset(data(), static_cast<int>(byte), mSize);
}

inline Memory::Buffer::Buffer(Buffer &&other)
  : mData{std::exchange(other.mData, nullptr)},
    mSize{std::exchange(other.mSize, 0)} {}

inline Memory::Buffer &Memory::Buffer::operator=(Buffer &&other) {
  dealloc(mData);
  mData = std::exchange(other.mData, nullptr);
  mSize = std::exchange(other.mSize, 0);
  return *this;
}

inline Memory::Buffer::~Buffer() {
  dealloc(mData);
}

inline bool Memory::Buffer::operator==(const Buffer &other) const {
  return mSize == other.mSize && std::memcmp(mData, other.mData, mSize) == 0;
}

inline bool Memory::Buffer::operator!=(const Buffer &other) const {
  return mSize != other.mSize || std::memcmp(mData, other.mData, mSize) != 0;
}

inline bool Memory::Buffer::operator<(const Buffer &other) const {
  if (mSize < other.mSize) {
    return true;
  } else if (other.mSize < mSize) {
    return false;
  } else {
    return std::memcmp(mData, other.mData, mSize) < 0;
  }
}

inline void Memory::Buffer::swap(Buffer &other) {
  std::swap(mData, other.mData);
  std::swap(mSize, other.mSize);
}

inline void Memory::Buffer::copyFrom(const Buffer &buffer) {
  std::memcpy(mData, buffer.mData, mSize < buffer.mSize ? mSize : buffer.mSize);
}

inline void Memory::Buffer::resize(const size_t size) {
  dealloc(mData);
  mData = allocBytes(size);
  mSize = size;
}

inline void Memory::Buffer::resizeCopy(const size_t size) {
  std::byte *const temp = allocBytes(size);
  std::memcpy(temp, mData, mSize < size ? mSize : size);
  dealloc(mData);
  mData = temp;
  mSize = size;
}
