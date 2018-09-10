//
//  op stack.hpp
//  Simpleton Engine
//
//  Created by Indi Kernick on 5/3/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_utils_op_stack_hpp
#define engine_utils_op_stack_hpp

#include <vector>
#include <cassert>
#include <type_traits>

namespace Utils {
  ///A stack that performs an operation on values when they are pushed
  template <typename STORED_TYPE, typename PUSHED_TYPE = STORED_TYPE>
  class OpStack {
  public:
    static_assert(
      std::is_destructible<STORED_TYPE>::value,
      "STORED_TYPE must be destructible"
    );
    static_assert(
      std::is_copy_assignable<STORED_TYPE>::value,
      "STORED_TYPE must be copy assignable"
    );

    OpStack() = delete;
    OpStack(size_t capacity, const STORED_TYPE &base)
      : stack() {
      stack.reserve(capacity);
      stack.push_back(base);
    }
    OpStack(const OpStack &) = delete;
    OpStack(OpStack &&) = default;
    virtual ~OpStack() = default;
    
    OpStack &operator=(const OpStack &) = delete;
    OpStack &operator=(OpStack &&) = default;
    
    void swap(OpStack &other) {
      std::swap(stack, other.stack);
    }
    
    void push(const PUSHED_TYPE &value) {
      stack.push_back(operation(stack.back(), value));
    }
    template <typename ...ARGS>
    void emplace(ARGS... args) {
      static_assert(
        std::is_constructible<PUSHED_TYPE, ARGS...>::value,
        "Arguments given cannot be used to construct PUSHED_TYPE"
      );
      
      stack.push_back(operation(
        stack.last(),
        PUSHED_TYPE(std::forward(args)...)
      ));
    }
    void pop() {
      assert(stack.size() > 1);
      stack.pop_back();
    }
    
    inline const STORED_TYPE &top() const {
      return stack.back();
    }
    size_t size() const {
      return stack.size() - 1;
    }
    bool empty() const {
      return stack.size() == 1;
    }
    
  private:
    std::vector<STORED_TYPE> stack;

    virtual STORED_TYPE operation(const STORED_TYPE &, const PUSHED_TYPE &) = 0;
  };
}

#endif
