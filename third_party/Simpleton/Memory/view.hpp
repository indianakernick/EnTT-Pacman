//
//  view.hpp
//  Simpleton Engine
//
//  Created by Indi Kernick on 26/09/2016.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef engine_memory_view_hpp
#define engine_memory_view_hpp

#include "buffer.hpp"

namespace Memory {
  ///A Primitive type memory view. For types that don't need their
  ///constructors and destructors called
  template <typename T>
  class View {
  public:
    explicit View(const size_t numObjects)
      : buf(numObjects * sizeof(T)) {}
    View(const size_t numObjects, const T obj)
      : buf(numObjects * sizeof(T)) {
      std::uninitialized_fill_n(data(), size(), obj);
    }
    View(T *data, const size_t numObjects)
      : buf(data, numObjects * sizeof(T)) {}
    
    View(View<T> &&) = default;
    View<T> &operator=(View<T> &&) = default;
    
    bool operator==(const View<T> &other) const {
      return buf == other.buf;
    }
    bool operator!=(const View<T> &other) const {
      return buf != other.buf;
    }
    bool operator<(const View<T> &other) const {
      return buf < other.buf;
    }
    
    void swap(View<T> &other) {
      buf.swap(other.buf);
    }
    void copyFrom(View<T> &other) {
      buf.copyFrom(other.buf);
    }
    
    T &operator[](const size_t i) {
      return *(begin() + i);
    }
    const T &operator[](const size_t i) const {
      return *(begin() + i);
    }
    
    T *data() {
      return buf.data<T>();
    }
    const T *data() const {
      return buf.data<T>();
    }
    const T *cdata() const {
      return buf.data<T>();
    }
    
    template <typename U = size_t>
    U size() const {
      return buf.size<U>() / sizeof(T);
    }
    
    T *begin() {
      return buf.begin<T>();
    }
    T *end() {
      return buf.end<T>();
    }
    
    const T *begin() const {
      return buf.begin<T>();
    }
    const T *end() const {
      return buf.end<T>();
    }
    
    const T *cbegin() const {
      return buf.cbegin<T>();
    }
    const T *cend() const {
      return buf.cend<T>();
    }
    
    Buffer buf;
  };
}

#endif
