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
  class Zero {};
  class One {};
  
  constexpr Zero ZERO_INIT {};
  constexpr One ONE_INIT {};

  class Buffer {
  public:
    explicit Buffer(size_t);
    Buffer(size_t, Zero);
    Buffer(size_t, One);
    Buffer(size_t, std::byte);
    
    Buffer(Buffer &&);
    Buffer &operator=(Buffer &&);
    ~Buffer();
    
    bool operator==(const Buffer &) const;
    bool operator!=(const Buffer &) const;
    bool operator<(const Buffer &) const;
    
    void swap(Buffer &);
    void copyFrom(const Buffer &);
    void resize(size_t);
    void resizeCopy(size_t);
    
    template <typename T = std::byte>
    T *data() {
      return reinterpret_cast<T *>(mData);
    }
    template <typename T = std::byte>
    const T *data() const {
      return reinterpret_cast<const T *>(mData);
    }
    template <typename T = std::byte>
    const T *cdata() const {
      return reinterpret_cast<const T *>(mData);
    }
    
    template <typename T = size_t>
    T size() const {
      return static_cast<T>(mSize);
    }
    
    template <typename T = std::byte>
    T *begin() {
      return reinterpret_cast<T *>(mData);
    }
    template <typename T = std::byte>
    T *end() {
      return reinterpret_cast<T *>(mData + mSize);
    }
    
    template <typename T = std::byte>
    const T *begin() const {
      return reinterpret_cast<const T *>(mData);
    }
    template <typename T = std::byte>
    const T *end() const {
      return reinterpret_cast<const T *>(mData + mSize);
    }
    
    template <typename T = std::byte>
    const T *cbegin() const {
      return reinterpret_cast<const T *>(mData);
    }
    template <typename T = std::byte>
    const T *cend() const {
      return reinterpret_cast<const T *>(mData + mSize);
    }
  
  private:
    std::byte *mData;
    size_t mSize;
  };
}

#include "buffer.inl"

#endif
