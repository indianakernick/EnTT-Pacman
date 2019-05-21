//
//  grid.hpp
//  Simpleton Engine
//
//  Created by Indi Kernick on 21/4/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#ifndef engine_grid_grid_hpp
#define engine_grid_grid_hpp

#include <array>
#include <vector>
#include "pos.hpp"
#include <utility>
#include "../Utils/numeric iterators.hpp"

namespace Grid {
  namespace detail {
    template <typename Derived, typename Tile>
    class GridBase {
    private:
      Derived &that() {
      	return *static_cast<Derived *>(this);
      }
      const Derived &that() const {
      	return *static_cast<const Derived *>(this);
      }

      void checkRange(const Pos pos) const {
        if (that().outOfRange(pos)) {
          throw std::range_error("Position out of range");
        }
      }
      void checkRange(const size_t index) const {
        if (that().outOfRange(index)) {
          throw std::range_error("Index out of range");
        }
      }
      
    public:
      auto begin() {
        return that().mTiles.begin();
      }
      auto begin() const {
        return that().mTiles.begin();
      }
      auto cbegin() const {
        return that().mTiles.begin();
      }
      auto end() {
        return that().mTiles.end();
      }
      auto end() const {
        return that().mTiles.end();
      }
      auto cend() const {
        return that().mTiles.end();
      }
      
      auto hori() const {
        return Utils::range(that().size().x);
      }
      auto vert() const {
        return Utils::range(that().size().y);
      }
      auto horiRev() const {
        return Utils::rangeRev(that().size().x);
      }
      auto vertRev() const {
        return Utils::rangeRev(that().size().y);
      }

      Tile &operator()(const Coord x, const Coord y) {
        return const_cast<Tile &>(std::as_const(*this).operator()(x, y));
      }
      const Tile &operator()(const Coord x, const Coord y) const {
        return that().mTiles[that().toIndex({x, y})];
      }
      Tile &operator[](const Pos pos) {
        return const_cast<Tile &>(std::as_const(*this).operator[](pos));
      }
      const Tile &operator[](const Pos pos) const {
        return that().mTiles[that().toIndex(pos)];
      }
      Tile &at(const Pos pos) {
        return const_cast<Tile &>(std::as_const(*this).at(pos));
      }
      const Tile &at(const Pos pos) const {
        checkRange(pos);
        return that().mTiles[that().toIndex(pos)];
      }
      
      Tile &operator[](const size_t index) {
        return const_cast<Tile &>(std::as_const(*this).operator[](index));
      }
      const Tile &operator[](const size_t index) const {
        assert(index < that().mTiles.size());
        return that().mTiles[index];
      }
      Tile &at(const size_t index) {
        return const_cast<Tile &>(std::as_const(*this).at(index));
      }
      const Tile &at(const size_t index) const {
        checkRange(index);
        return that().mTiles[index];
      } 
    };
  }
  
  constexpr Coord runtime = 0;

  template <typename Tile_, Coord Width_ = runtime, Coord Height_ = runtime>
  class Grid final : public detail::GridBase<Grid<Tile_, Width_, Height_>, Tile_> {
  public:
    friend detail::GridBase<Grid, Tile_>;
  
    using Tile = Tile_;
    static constexpr Coord Width = Width_;
    static constexpr Coord Height = Height_;
    using Tiles = std::array<Tile, Width * Height>;
    
    static_assert(Width > 0);
    static_assert(Height > 0);
    
    Grid() = default;
    // So that dynamic and static grids have compatible interfaces
    Grid(const Coord width, const Coord height) {
      assert(width == Width);
      assert(height == Height);
    }
    explicit Grid(const Pos size)
      : Grid{size.x, size.y} {}
    Grid(const Pos size, const Tile &tile)
      : Grid{size} {
      mTiles.fill(tile);
    }
    explicit Grid(const Tile &tile) {
      mTiles.fill(tile);
    }

    void fill(const Tile &tile) {
      mTiles.fill(tile);
    }

    static constexpr Pos size() {
      return {Width, Height};
    }
    static constexpr Coord width() {
      return Width;
    }
    static constexpr Coord height() {
      return Height;
    }
    static constexpr size_t area() {
      return static_cast<size_t>(Width * Height);
    }
    
    static bool outOfRange(const Pos pos) {
      return pos.x < 0 || pos.y < 0 || pos.x >= Width || pos.y >= Height;
    }
    static bool outOfRange(const size_t index) {
      return index >= Width * Height;
    }

    static size_t toIndex(const Pos pos) {
      assert(!outOfRange(pos));
      return pos.y * Width + pos.x;
    }
    static Pos toPos(const size_t index) {
      assert(!outOfRange(index));
      const Coord cindex = static_cast<Coord>(index);
      return {cindex % Width, cindex / Width};
    }
  
  private:
    Tiles mTiles;
  };

  template <typename Tile_>
  class Grid<Tile_, runtime, runtime> final : public detail::GridBase<Grid<Tile_, runtime, runtime>, Tile_> {
  public:
    friend detail::GridBase<Grid, Tile_>;
  
    using Tile = Tile_;
    using Tiles = std::vector<Tile>;
  
    Grid()
      : mSize(0, 0) {}
    Grid(const Coord width, const Coord height, const Tile &tile = {})
      : mTiles{static_cast<size_t>(width * height), tile},
        mSize{width, height} {
      assert(width > 0);
      assert(height > 0);
    }
    explicit Grid(const Pos size, const Tile &tile = {})
      : Grid{size.x, size.y, tile} {}
    
    void clear() {
      mTiles.clear();
      mSize = {0, 0};
    }
    void resize(const Pos size, const Tile &tile = {}) {
      assert(size.x > 0);
      assert(size.y > 0);
      mTiles.resize(static_cast<size_t>(size.x * size.y), tile);
      mSize = size;
    }
    void fill(const Tile &tile) {
      std::fill(mTiles.begin(), mTiles.end(), tile);
    }
    
    Pos size() const {
      return mSize;
    }
    Coord width() const {
      return mSize.x;
    }
    Coord height() const {
      return mSize.y;
    }
    size_t area() const {
      return mTiles.size();
    }
    
    bool outOfRange(const Pos pos) const {
      return pos.x < 0 || pos.y < 0 || pos.x >= mSize.x || pos.y >= mSize.y;
    }
    bool outOfRange(const size_t index) const {
      return index >= mTiles.size();
    }
    
    size_t toIndex(const Pos pos) const {
      assert(!outOfRange(pos));
      return pos.y * mSize.x + pos.x;
    }
    Pos toPos(const size_t index) const {
      assert(!outOfRange(index));
      const Coord cindex = static_cast<Coord>(index);
      return {cindex % mSize.x, cindex / mSize.x};
    }
  
  private:
    Tiles mTiles;
    Pos mSize;
  };
}

#endif
