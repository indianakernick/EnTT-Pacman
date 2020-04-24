//
//  instance limiter.hpp
//  Simpleton Engine
//
//  Created by Indi Kernick on 8/10/2016.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef engine_utils_instance_limiter_hpp
#define engine_utils_instance_limiter_hpp

#include <exception>

namespace Utils {
  class TooManyInstances : public std::exception {};

  template <typename T>
  class TooManyInstancesOf final : public TooManyInstances {
  public:
    const char *what() const noexcept override {
      return "Too many instances";
    }
  };
}

// this is causing some problems with UTILS_RAII_CLASS
#define DISABLE_INSTANCE_LIMITER

#ifndef DISABLE_INSTANCE_LIMITER

namespace Utils {
  ///Limit the number of instances of a derived class
  template <typename T, size_t MAX_COUNT>
  class LimitInstances {
  private:
    static void checkCount() {
      if (count > MAX_COUNT) {
        throw TooManyInstancesOf<T>{};
      }
    }

  protected:
    LimitInstances() {
      count++;
      checkCount();
    }
    LimitInstances(const LimitInstances &) {
      count++;
      checkCount();
    }
    LimitInstances(LimitInstances &&) {
      count++;
    }
    ~LimitInstances() {
      static_assert(std::is_base_of<LimitInstances, T>::value);
      count--;
    }
    
    LimitInstances &operator=(const LimitInstances &) = default;
    LimitInstances &operator=(LimitInstances &&) = default;

  private:
    static size_t count;
  };

  template <typename T, size_t MAX_COUNT>
  size_t LimitInstances<T, MAX_COUNT>::count = 0;

  ///Limit the number of instances of a derived class
  template <typename T>
  class LimitInstances<T, 1> {
  protected:
    LimitInstances() {
      if (created) {
        throw TooManyInstancesOf<T>{};
      } else {
        created = true;
      }
    }
    LimitInstances(const LimitInstances &) = delete;
    LimitInstances(LimitInstances &&) = default;
    ~LimitInstances() {
      static_assert(std::is_base_of<LimitInstances, T>::value);
      created = false;
    }
    
    LimitInstances &operator=(const LimitInstances &) = delete;
    LimitInstances &operator=(LimitInstances &&) = default;

  public:
    static bool wasCreated() {
      return created;
    }
    
  private:
    static bool created;
  };

  template <typename T>
  bool LimitInstances<T, 1>::created = false;
}

#else

namespace Utils {
  ///Limit the number of instances of a derived class
  template <typename T, size_t>
  class LimitInstances {
  protected:
    LimitInstances() = default;
    LimitInstances(const LimitInstances &) = default;
    LimitInstances(LimitInstances &&) = default;
    ~LimitInstances() {
      static_assert(std::is_base_of<LimitInstances, T>::value);
    }
    
    LimitInstances &operator=(const LimitInstances &) = default;
    LimitInstances &operator=(LimitInstances &&) = default;
  };

  ///Limit the number of instances of a derived class
  template <typename T>
  class LimitInstances<T, 1> {
  protected:
    LimitInstances() = default;
    LimitInstances(const LimitInstances &) = delete;
    LimitInstances(LimitInstances &&) = default;
    ~LimitInstances() {
      static_assert(std::is_base_of<LimitInstances, T>::value);
    }
    
    LimitInstances &operator=(const LimitInstances &) = delete;
    LimitInstances &operator=(LimitInstances &&) = default;
  
  public:
    static bool wasCreated() {
      return true;
    }
  };
}

#endif

namespace Utils {
  ///Limit the number of instances of a derived class
  template <typename T>
  class LimitInstances<T, 0> {
  protected:
    LimitInstances() = delete;
    LimitInstances(const LimitInstances &) = delete;
    LimitInstances(LimitInstances &&) = delete;
    ~LimitInstances() = delete;
    
    LimitInstances &operator=(const LimitInstances &) = delete;
    LimitInstances &operator=(LimitInstances &&) = delete;
  };

  ///Force a derived class to be a singleton
  template <typename T>
  using ForceSingleton = LimitInstances<T, 1>;
  
  ///Force a derived class to never be constructed. The resulting class will be
  ///a symbol
  template <typename T>
  using ForceSymbol = LimitInstances<T, 0>;
  
  ///Force a derived class to never be constructed. The resulting class will be
  ///a static class
  template <typename T>
  using ForceStaticClass = LimitInstances<T, 0>;
}

#define MAKE_SYMBOL(NAME) struct NAME : Utils::ForceSymbol<NAME> {}

#endif
