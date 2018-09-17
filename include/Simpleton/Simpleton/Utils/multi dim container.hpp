//
//  multi dim array adapter.hpp
//  Simpleton Engine
//
//  Created by Indi Kernick on 15/6/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_utils_multi_dim_array_adapter_hpp
#define engine_utils_multi_dim_array_adapter_hpp

#include <vector>
#include "multi dim array.hpp"

namespace Utils {
  template <typename ElementType, typename MultiDimArray>
  class MultiDimIterator {
  public:
    using Coords = typename MultiDimArray::Coords;
    using AccessIndex = typename MultiDimArray::AccessIndex;
    
    using difference_type = ptrdiff_t;
    using value_type = ElementType;
    using pointer = value_type *;
    using reference = value_type &;
    using iterator_category = std::random_access_iterator_tag;
  
    MultiDimIterator(
      ElementType *base,
      const Coords pos,
      const Coords capacity,
      const Coords begin,
      const Coords end
    ) : base(base),
        pos(pos),
        capacity(capacity),
        begin(begin),
        end(end) {}
  
    bool operator==(const MultiDimIterator &other) const {
      return base == other.base &&
             pos == other.pos &&
             capacity == other.capacity &&
             begin == other.begin &&
             end == other.end;
    }
    bool operator!=(const MultiDimIterator &other) const {
      return base != other.base ||
             pos != other.pos ||
             capacity != other.capacity ||
             begin != other.begin ||
             end != other.end;
    }
  
    MultiDimIterator &operator+=(const difference_type advance) {
      pos = MultiDimArray::nextPosAligned(pos, begin, end, advance);
      return *this;
    }
    MultiDimIterator &operator-=(const difference_type advance) {
      pos = MultiDimArray::prevPosAligned(pos, begin, end, advance);
      return *this;
    }
    
    MultiDimIterator operator+(const difference_type advance) const {
      return {
        base,
        MultiDimArray::nextPosAligned(pos, begin, end, advance),
        capacity,
        begin,
        end
      };
    }
    MultiDimIterator operator-(const difference_type advance) const {
      return {
        base,
        MultiDimArray::prevPosAligned(pos, begin, end, advance),
        capacity,
        begin,
        end
      };
    }
    
    difference_type operator-(const MultiDimIterator other) const {
      difference_type product = 1;
      bool neg = false;
      for (AccessIndex i = 0; i != MultiDimArray::DIMENSIONS; i++) {
        const difference_type diff(pos[i] - other.pos[i]);
        if (diff < 0) {
          neg = true;
          product *= -diff;
        } else {
          product *= diff;
        }
      }
      return neg ? -product : product;
    }
    
    MultiDimIterator &operator++() {
      pos = MultiDimArray::nextPosAligned(pos, begin, end);
      return *this;
    }
    MultiDimIterator &operator--() {
      pos = MultiDimArray::prevPosAligned(pos, begin, end);
      return *this;
    }
    
    MultiDimIterator operator++(int) {
      const MultiDimIterator copy = *this;
      pos = MultiDimArray::nextPosAligned(pos, begin, end);
      return copy;
    }
    MultiDimIterator operator--(int) {
      const MultiDimIterator copy = *this;
      pos = MultiDimArray::prevPosAligned(pos, begin, end);
      return copy;
    }
    
    ElementType &operator*() const {
      return base[MultiDimArray::posToIndex(pos, capacity)];
    }
    ElementType *operator->() const {
      return base + MultiDimArray::posToIndex(pos, capacity);
    }
    
    Coords getPos() const {
      return pos;
    }
    size_t getIndex() const {
      return MultiDimArray::posToIndex(pos, capacity);
    }
    
  private:
    ElementType *base;
    Coords pos;
    Coords capacity;
    Coords begin;
    Coords end;
  };
  
  class Size {};
  class Capacity {};
  
  static constexpr Size SIZE = {};
  static constexpr Capacity CAPACITY = {};

  template <typename ElementType, size_t DIMS, Order ORDER, typename CoordType, typename IndexType>
  class MultiDimContainer {
  public:
    using Container = std::vector<ElementType>;
    using MultiDimArray = MultiDimArray<DIMS, ORDER, CoordType, IndexType>;

    using Coords = typename MultiDimArray::Coords;
    using AccessIndex = typename MultiDimArray::AccessIndex;
    using Traits = typename MultiDimArray::Traits;

    using iterator = MultiDimIterator<ElementType, MultiDimArray>;
    using const_iterator = MultiDimIterator<const ElementType, MultiDimArray>;

    MultiDimContainer(Size, const Coords size)
      : mContainer(calcSize(size)), mCapacity(size), mSize(size) {}
    MultiDimContainer(Capacity, const Coords capacity)
      : mContainer(calcSize(capacity)), mCapacity(capacity), mSize(Traits::ZERO) {}
    MultiDimContainer(const Coords size, const Coords capacity)
      : mContainer(calcSize(capacity)), mCapacity(capacity), mSize(size) {
      if (Traits::anyLess(capacity, size)) {
        throw BadSize();
      }
    }
    
    Container &getContainer() {
      return mContainer;
    }
    const Container &getContainer() const {
      return mContainer;
    }
    
    void reserve(const Coords newSize) {
      if (Traits::anyLess(mCapacity, newSize)) {
        mCapacity = newSize;
        mContainer.resize(calcSize(newSize));
      }
    }
    Coords capacity() const {
      return mCapacity;
    }
    
    void resize(const Coords newSize) {
      if (Traits::anyLess(mCapacity, newSize)) {
        throw BadSize();
      }
      mSize = newSize;
    }
    Coords size() const {
      return mSize;
    }
    
    ElementType &access(const Coords pos) {
      return mContainer[MultiDimArray::posToIndex(pos, mSize)];
    }
    const ElementType &access(const Coords pos) const {
      return mContainer[MultiDimArray::posToIndex(pos, mSize)];
    }
    
    size_t index(const Coords pos) const {
      return MultiDimArray::posToIndex(pos, mSize);
    }
    Coords pos(const size_t index) const {
      return MultiDimArray::indexToPos(index, mSize);
    }
    
    ElementType &access(const size_t index) {
      return mContainer[index];
    }
    const ElementType &access(const size_t index) const {
      return mContainer[index];
    }
    
    iterator begin() {
      return {
        mContainer.data(),
        MultiDimArray::Traits::ZERO,
        mCapacity,
        MultiDimArray::Traits::ZERO,
        mSize
      };
    }
    iterator end() {
      return {
        mContainer.data(),
        mSize,
        mCapacity,
        MultiDimArray::Traits::ZERO,
        mSize
      };
    }
    const_iterator cbegin() const {
      return {
        mContainer.data(),
        MultiDimArray::Traits::ZERO,
        mCapacity,
        MultiDimArray::Traits::ZERO,
        mSize
      };
    }
    const_iterator cend() const {
      return {
        mContainer.data(),
        mSize,
        mCapacity,
        MultiDimArray::Traits::ZERO,
        mSize
      };
    }
    
    iterator begin(const Coords begin, const Coords end) {
      return {mContainer.data(), begin, mCapacity, begin, end};
    }
    iterator end(const Coords begin, const Coords end) {
      return {mContainer.data(), end, mCapacity, begin, end};
    }
    const_iterator cbegin(const Coords begin, const Coords end) const {
      return {mContainer.data(), begin, mCapacity, begin, end};
    }
    const_iterator cend(const Coords begin, const Coords end) const {
      return {mContainer.data(), end, mCapacity, begin, end};
    }
  
  private:
    Container mContainer;
    Coords mCapacity;
    Coords mSize;
    
    static size_t calcSize(const Coords size) {
      size_t product = 1;
      for (AccessIndex i = 0; i != MultiDimArray::DIMENSIONS; i++) {
        product *= size[i];
      }
      return product;
    }
  };
}

#endif
