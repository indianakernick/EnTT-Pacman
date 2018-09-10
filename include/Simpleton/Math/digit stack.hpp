//
//  digit stack.hpp
//  Simpleton Engine
//
//  Created by Indi Kernick on 29/11/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_math_digit_stack_hpp
#define engine_math_digit_stack_hpp

#include <cmath>

namespace Math {
  /*
  A fast alternative to this
  
  void bad() {
    std::string digits;
    digits.push_back('1');
    digits.push_back('2');
    digits.push_back('3');
    int number;
    std::from_chars(digits.data(), digits.data() + digits.size(), number);
    // number == 123
  }
  
  void good() {
    Math::DigitStack<int> stack;
    stack.push(1);
    stack.push(2);
    stack.push(3);
    int number = stack.get();
    // number == 123
  }
  */

  template <typename Value_, unsigned long long base_ = 10>
  class DigitStack {
  public:
    using Value = Value_;
    static constexpr Value base = static_cast<Value>(base_);
    
    static_assert(base > Value(1));

    DigitStack() = default;
    explicit DigitStack(const Value val)
      : val{val} {
      assert(val >= Value(0));
      if (val == Value(0)) {
        numDigits = 1;
      } else {
        numDigits = std::log2(val) / std::log2(base) + 1.0;
      }
    }
    
    void push(const Value digit) {
      val = val * base + digit;
      ++numDigits;
    }
    void pop() {
      if (numDigits != 0) {
        val /= base;
        --numDigits;
      }
    }
    void clear() {
      val = 0;
      numDigits = 0;
    }
    
    Value get() const {
      return val;
    }
    bool empty() const {
      return numDigits == 0;
    }
    unsigned char size() const {
      return numDigits;
    }
    
  private:
    Value val = 0;
    unsigned char numDigits = 0;
  };
}

#endif
