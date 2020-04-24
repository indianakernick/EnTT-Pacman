//
//  block allocator.hpp
//  Simpleton Engine
//
//  Created by Indi Kernick on 15/10/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_memory_block_allocator_hpp
#define engine_memory_block_allocator_hpp

#include <cstring>
#include <exception>
#include "alloc.hpp"
#include <type_traits>

namespace Memory {
  enum class AllocFail {
    throw_bad_alloc,
    return_nullptr,
    terminate
  };

  class BadFreePtr final : public std::exception {
  public:
    BadFreePtr() = default;
    
    inline const char *what() const noexcept override {
      return "Attempt to dealloc invalid pointer";
    }
  };

  template <typename Object_, size_t BLOCK_SIZE_, AllocFail FAIL_ = AllocFail::throw_bad_alloc>
  class BlockAllocator {
  public:
    using Object = Object_;
    static constexpr size_t BLOCK_SIZE = BLOCK_SIZE_;
    static constexpr AllocFail FAIL = FAIL_;
    
    static_assert(std::is_default_constructible_v<Object>, "Object must be default constructible");
    static_assert(std::is_destructible_v<Object>, "Object must be destructible");
    static_assert(BLOCK_SIZE != 0, "Block size must be greater than 0");
  
  private:
    union Block {
      Block *nextFree;
      Object objects[BLOCK_SIZE];
    };
  
  public:
    explicit BlockAllocator(const size_t numBlocks)
      : blocks{allocArr<Block>(numBlocks)},
        numBlocks{numBlocks},
        head{blocks},
        allocations{0} {
      if (numBlocks != 0) {
        Block *prevBlock = blocks;
        Block *const lastBlock = blocks + (numBlocks - 1);
        while (prevBlock != lastBlock) {
          Block *const nextBlock = prevBlock + 1;
          prevBlock->nextFree = nextBlock;
          prevBlock = nextBlock;
        }
      }
    }
    ~BlockAllocator() {
      Memory::dealloc(blocks);
    }
    
    BlockAllocator(BlockAllocator &&) = default;
    BlockAllocator &operator=(BlockAllocator &&) = default;
    
    /// Are there any free blocks available for allocation?
    bool canAlloc() const {
      return head;
    }
    /// How many blocks have been allocated?
    size_t allocCount() const {
      return allocations;
    }
    /// How many blocks have not been allocated?
    size_t freeCount() const {
      return numBlocks - allocations;
    }
    
    /// Allocate a block
    Object *alloc() {
      if (head == nullptr) {
        if constexpr (FAIL == AllocFail::throw_bad_alloc) {
          throw std::bad_alloc();
        } else if constexpr (FAIL == AllocFail::return_nullptr) {
          return nullptr;
        } else if constexpr (FAIL == AllocFail::terminate) {
          std::terminate();
        }
      }
      ++allocations;
      Block *const newBlock = head;
      head = head->nextFree;
      return newBlock->objects;
    }
    
    /// Deallocate a block
    void dealloc(Object *const object) {
      if (object == nullptr) {
        return;
      }
      rangeCheck(object);
      Block *const block = reinterpret_cast<Block *>(object);
      block->nextFree = head;
      head = block;
      --allocations;
    }
    
    /// Allocate a block and default construct the objects
    Object *allocDefContruct() {
      Object *const objs = alloc();
      if constexpr (FAIL == AllocFail::return_nullptr) {
        if (objs == nullptr) {
          return nullptr;
        }
      }
      if constexpr (std::is_trivially_default_constructible_v<Object>) {
        std::memset(objs, 0, sizeof(Block));
        return objs;
      } else if constexpr (std::is_default_constructible_v<Object>) {
        new (objs) Object[BLOCK_SIZE];
        return objs;
      }
    }
    
    /// Allocate a block, construct a temporary object from the provided args
    /// and copy construct the objects with the temporary
    template <typename... Args>
    Object *allocCopyConstruct(Args &&... args) {
      Object *const objs = alloc();
      if constexpr (FAIL == AllocFail::return_nullptr) {
        if (objs == nullptr) {
          return nullptr;
        }
      }
      const Object copy{std::forward<Args>(args)...};
      Object *const end = objs + BLOCK_SIZE;
      for (Object *o = objs; o != end; ++o) {
        new (o) Object{copy};
      }
      return objs;
    }
    
    /// Allocate a block and construct a single object with the provided args
    template <typename... Args>
    Object *allocMoveConstruct(Args &&... args) {
      static_assert(BLOCK_SIZE == 1);
      Object *const obj = alloc();
      if constexpr (FAIL == AllocFail::return_nullptr) {
        if (obj == nullptr) {
          return nullptr;
        }
      }
      new (obj) Object{std::forward<Args>(args)...};
      return obj;
    }
    
    /// Deallocate a block and destroy the objects
    void deallocDestroy(Object *const object) {
      if (object == nullptr) {
        return;
      }
      rangeCheck(object);
      if constexpr (!std::is_trivially_destructible_v<Object>) {
        Object *const end = object + BLOCK_SIZE;
        for (Object *o = object; o != end; ++o) {
          o->~Object();
        }
      }
      Block *const block = reinterpret_cast<Block *>(object);
      block->nextFree = head;
      head = block;
      --allocations;
    }
  
  private:
    Block *blocks;
    size_t numBlocks;
    Block *head;
    size_t allocations;
    
    void rangeCheck(const Object *const object) {
      const uintptr_t objectInt = reinterpret_cast<uintptr_t>(object);
      const uintptr_t firstInt = reinterpret_cast<uintptr_t>(blocks);
      const uintptr_t lastInt = reinterpret_cast<uintptr_t>(blocks + BLOCK_SIZE);
      if (objectInt < firstInt || objectInt >= lastInt) {
        throw BadFreePtr{}; // Not within the pool
      }
      if ((objectInt - firstInt) % sizeof(Block) != 0) {
        throw BadFreePtr{}; // Not aligned properly
      }
    }
  };
}

#endif
