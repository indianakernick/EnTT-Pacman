//
//  buffer.hpp
//  Simpleton Engine
//
//  Created by Indi Kernick on 25/09/2016.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef engine_memory_buffer_hpp
#define engine_memory_buffer_hpp

#include "alloc.hpp"

namespace Memory {
  /// A dynamically allocated sequence of bytes. Essentially a low-level,
  /// lightweight replacement for std::vector<std::byte>
  class Buffer {
  public:
    /// Allocate a buffer of the given size in bytes. Bytes are not initialized
    explicit Buffer(size_t) noexcept;
    /// Allocate a buffer of the given size in bytes. Initialize each byte to
    /// the given value
    Buffer(size_t, std::byte) noexcept;
    
    Buffer(Buffer &&) noexcept;
    Buffer &operator=(Buffer &&) noexcept;
    ~Buffer() noexcept;
    
    bool operator==(const Buffer &) const noexcept;
    bool operator!=(const Buffer &) const noexcept;
    bool operator<(const Buffer &) const noexcept;
    bool operator>(const Buffer &) const noexcept;
    bool operator<=(const Buffer &) const noexcept;
    bool operator>=(const Buffer &) const noexcept;
    
    /// Swap this buffer with the given buffer
    void swap(Buffer &) noexcept;
    /// Copy bytes from the given buffer to this buffer.
    /// If other.size < this->size(), the data is truncated.
    /// If other.size > this->size(), the remaining bytes are untouched.
    void copyFrom(const Buffer &) noexcept;
    /// Copy bytes from the given buffer to this buffer.
    /// If other.size < this->size(), the data is truncated.
    /// If other.size > this->size(), the remaining bytes are initialized to the
    /// given value
    void copyFrom(const Buffer &, std::byte) noexcept;
    
    /// Create a new buffer and copy the bytes of this buffer to the new one
    Buffer dup() const noexcept;
    /// Create a new buffer of the given size and copy the bytes of this buffer
    /// to the new one as if by buf.copyFrom(*this)
    Buffer dup(size_t) const noexcept;
    /// Create a new buffer of the given size and copy the bytes of this buffer
    /// to the new one as if by buf.copyFrom(*this, byte)
    Buffer dup(size_t, std::byte) const noexcept;
    
    /// Initialize all bytes to zero
    void zero() noexcept;
    /// All bytes to the given value
    void fill(std::byte) noexcept;
    /// Set the first n bytes to the given value
    void fillFirst(size_t, std::byte) noexcept;
    /// Set the last n bytes to the given value
    void fillLast(size_t, std::byte) noexcept;
    
    /// Return a pointer to the first occurance of a given byte or nullptr if
    /// not found
    std::byte *findPtr(std::byte) noexcept;
    /// Return a pointer to the first occurance of a given byte or nullptr if
    /// not found
    const std::byte *findPtr(std::byte) const noexcept;
    /// Return the index of the first occurance of a given byte or ~size_t{} if
    /// not found
    size_t findIdx(std::byte) const noexcept;
    
    template <typename T = std::byte>
    T *data() noexcept {
      return reinterpret_cast<T *>(mData);
    }
    template <typename T = std::byte>
    const T *data() const noexcept {
      return reinterpret_cast<const T *>(mData);
    }
    template <typename T = std::byte>
    const T *cdata() const noexcept {
      return reinterpret_cast<const T *>(mData);
    }
    
    template <typename T = size_t>
    T size() const noexcept {
      return static_cast<T>(mSize);
    }
    
    template <typename T = std::byte>
    T *begin() noexcept {
      return reinterpret_cast<T *>(mData);
    }
    template <typename T = std::byte>
    T *end() noexcept {
      return reinterpret_cast<T *>(mData + mSize);
    }
    
    template <typename T = std::byte>
    const T *begin() const noexcept {
      return reinterpret_cast<const T *>(mData);
    }
    template <typename T = std::byte>
    const T *end() const noexcept {
      return reinterpret_cast<const T *>(mData + mSize);
    }
    
    template <typename T = std::byte>
    const T *cbegin() const noexcept {
      return reinterpret_cast<const T *>(mData);
    }
    template <typename T = std::byte>
    const T *cend() const noexcept {
      return reinterpret_cast<const T *>(mData + mSize);
    }
  
  private:
    std::byte *mData;
    size_t mSize;
  };
  
  /// Swap a pair of buffers
  inline void swap(Buffer &, Buffer &) noexcept;
}

#include "buffer.inl"

#endif
