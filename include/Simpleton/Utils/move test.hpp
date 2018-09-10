//
//  move test.hpp
//  Simpleton Engine
//
//  Created by Indi Kernick on 18/12/16.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef engine_utils_move_test_hpp
#define engine_utils_move_test_hpp

#include <iostream>
#include "type name.hpp"

namespace Utils {
  template <typename T>
  class MoveTest {
  public:
    MoveTest() {
      if (logging) {
        std::cerr << typeName<T>() << " - Default constructor\n";
      }
    }
    MoveTest(const MoveTest &) {
      if (logging) {
        std::cerr << typeName<T>() << " - Copy constructor\n";
      }
    }
    MoveTest(MoveTest &&) {
      if (logging) {
        std::cerr << typeName<T>() << " - Move constructor\n";
      }
    }
    
    virtual ~MoveTest() {
      if (logging) {
        std::cerr << typeName<T>() << " - Destructor\n";
      }
    }
    
    MoveTest &operator=(const MoveTest &) {
      if (logging) {
        std::cerr << typeName<T>() << " - Copy assignment\n";
      }
      return *this;
    }
    MoveTest &operator=(MoveTest &&) {
      if (logging) {
        std::cerr << typeName<T>() << " - Move assignment\n";
      }
      return *this;
    }
    
    static MoveTest rValue() {
      return {};
    }
    static const MoveTest lValue;
    
    static void startLogging() {
      logging = true;
    }
    static void stopLogging() {
      logging = false;
    }
    
  private:
    static bool logging;
  };

  template <typename T>
  const MoveTest<T> MoveTest<T>::lValue = {};

  template <typename T>
  bool MoveTest<T>::logging = false;

  template <typename T>
  class MoveCounter {
  public:
    struct Count {
      int defaultCtor = 0;
      int copyCtor = 0;
      int moveCtor = 0;
      int dtor = 0;
      int copyAssign = 0;
      int moveAssign = 0;
    };
    
    MoveCounter() {
      count.defaultCtor++;
    }
    MoveCounter(const MoveCounter &) {
      count.copyCtor++;
    }
    MoveCounter(MoveCounter &&) {
      count.moveCtor++;
    }
    
    virtual ~MoveCounter() {
      count.dtor++;
    }
    
    MoveCounter &operator=(const MoveCounter &) {
      count.copyAssign++;
      return *this;
    }
    MoveCounter &operator=(MoveCounter &&) {
      count.moveAssign++;
      return *this;
    }
    
    static const Count &getCount() {
      return count;
    }
    static void logCount() {
      std::cerr << "\nDefault constructor  " << count.defaultCtor
                << "\nCopy constructor     " << count.copyCtor
                << "\nMove constructor     " << count.moveCtor
                << "\nDestructor           " << count.dtor
                << "\nCopy assign          " << count.copyAssign
                << "\nMove assign          " << count.moveAssign
                << '\n'
                << '\n';
    }
    static void resetCount() {
      count = {};
    }
    
  private:
    static Count count;
  };

  template <typename T>
  typename MoveCounter<T>::Count MoveCounter<T>::count;
}

#endif
