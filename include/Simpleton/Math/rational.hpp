//
//  rational.hpp
//  Simpleton Engine
//
//  Created by Indi Kernick on 29/5/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#ifndef engine_math_rational_hpp
#define engine_math_rational_hpp

#include <limits>
#include <numeric>
#include <type_traits>

namespace Math {
  struct Rational {
    intmax_t n;
    intmax_t d;
    
    constexpr Rational()
      : n{0}, d{1} {}
    
    // not explicit
    constexpr Rational(const intmax_t i)
      : n{i}, d{1} {}
    
    constexpr Rational(const intmax_t n, const intmax_t d)
      : n{n}, d{d} {}
    
    constexpr bool eq(Rational) const;
    constexpr bool ne(Rational) const;
    constexpr bool lt(Rational) const;
    constexpr bool le(Rational) const;
    constexpr bool gt(Rational) const;
    constexpr bool ge(Rational) const;
  };
 
  constexpr intmax_t ratio_num_max = std::numeric_limits<intmax_t>::max();
  constexpr intmax_t ratio_num_min = std::numeric_limits<intmax_t>::min();
  constexpr intmax_t ratio_den_max = ratio_num_max;
  constexpr intmax_t ratio_den_min = ratio_num_min;
  constexpr Rational ratio_max = {ratio_num_max, 1};
  constexpr Rational ratio_min = {ratio_num_max, 1};
  // the lowest number that is greater than one is {ratio_max_num, ratio_max_den - 1}
  // epsilon is the difference between that and one
  constexpr Rational ratio_eps = {1, ratio_den_max - 1};
  constexpr Rational ratio_inf = {ratio_num_max, 0};
  constexpr Rational ratio_nan = {0, 0};
  constexpr Rational ratio_one = {1, 1};
  constexpr Rational ratio_zero = {0, 1};
  
  constexpr bool operator==(const Rational a, const Rational b) {
    return a.n == b.n && a.d == b.d;
  }
  constexpr bool operator!=(const Rational a, const Rational b) {
    return !(a == b);
  }
  constexpr bool operator<(const Rational a, const Rational b) {
    return a.n * b.d < b.n * a.d;
  }
  constexpr bool operator<=(const Rational a, const Rational b) {
    return !(b < a);
  }
  constexpr bool operator>(const Rational a, const Rational b) {
    return b < a;
  }
  constexpr bool operator>=(const Rational a, const Rational b) {
    return !(a < b);
  }
  
  static_assert(Rational{2, 4} == Rational{2, 4});
  static_assert(Rational{7, 49} < Rational{6, 36});
  static_assert(Rational{-6, 36} < Rational{7, 49});
  
  /// Convert the rational to a floating point
  template <typename Float = double>
  constexpr Float toFloat(const Rational rat) {
    static_assert(std::is_floating_point_v<Float>);
    return static_cast<Float>(rat.n) / static_cast<Float>(rat.d);
  }
  
  /// Convert the non-repeating floating point number to a rational.
  /// This is for fractions that don't produce repeating digits in decimal.
  /// (1/4, 6/5, 3/8)
  template <intmax_t Precision = 1000000, typename Float>
  constexpr Rational fromFloat(const Float f) {
    static_assert(std::is_floating_point_v<Float>);
    const Float round = f < Float(0) ? Float(-0.5) : Float(0.5);
    const intmax_t numer = round + f * Precision;
    const intmax_t gcd = std::gcd(numer, Precision);
    return {numer / gcd, Precision / gcd};
  }
  
  /// Convert the repeating floating point number to a rational. This is for
  /// fractions that produce repeating digits in decimal. (1/7, 2/9, 3/11)
  /// There must be enough precision to represent an integer number of repeating
  /// sequences
  template <intmax_t Precision = 1000000, typename Float>
  constexpr Rational fromRepFloat(const Float f) {
    return fromFloat<Precision - 1>(f);
  }
  
  static_assert(fromRepFloat<1000000>(0.142857) == Rational{1, 7});
  static_assert(fromRepFloat<10>(0.2222) == Rational{2, 9});
  static_assert(fromFloat<10>(0.5) == Rational{1, 2});
  static_assert(fromFloat<1000>(0.375) == Rational{3, 8});
  
  static_assert(fromRepFloat<1000000>(-0.142857) == Rational{-1, 7});
  static_assert(fromRepFloat<10>(-0.2222) == Rational{-2, 9});
  static_assert(fromFloat<10>(-0.5) == Rational{-1, 2});
  static_assert(fromFloat<1000>(-0.375) == Rational{-3, 8});
  
  struct Proper {
    intmax_t integral;
    Rational frac;
  };
  
  /// Convert the improper fraction to a proper fraction
  constexpr Proper toProper(const Rational rat) {
    return {rat.n / rat.d, {rat.n % rat.d, rat.d}};
  }
  
  /// Convert the proper fraction to an improper fraction
  constexpr Rational fromProper(const Proper prop) {
    return {prop.integral * prop.frac.d + prop.frac.n, prop.frac.d};
  }
  
  /// Normalize the sign of the numerator and denominator such that positive
  /// rationals {n > 0, d > 0} and negative rationals {n < 0, d > 0}
  constexpr Rational normSign(const Rational rat) {
    if (rat.d < 0) {
      return {-rat.n, -rat.d};
    } else {
      return rat;
    }
  }
  
  static_assert(normSign({4, -5}) == Rational{-4, 5});
  static_assert(normSign({-2, -7}) == Rational{2, 7});
  
  /// Normalize the numerator and denominator to their lowest possible values
  /// such that 4/8 becomes 1/2
  constexpr Rational norm(const Rational rat) {
    const intmax_t gcd = std::gcd(rat.n, rat.d);
    return normSign({
      rat.n / gcd,
      rat.d / gcd
    });
  }
  
  static_assert(norm({25, 125}) == Rational{1, 5});
  static_assert(norm({2, 7}) == Rational{2, 7});
  static_assert(norm({2, -8}) == Rational{-1, 4});
  
  constexpr bool Rational::eq(const Rational other) const {
    return norm(*this) == norm(other);
  }
  constexpr bool Rational::ne(const Rational other) const {
    return norm(*this) != norm(other);
  }
  constexpr bool Rational::lt(const Rational other) const {
    return normSign(*this) < normSign(other);
  }
  constexpr bool Rational::le(const Rational other) const {
    return normSign(*this) <= normSign(other);
  }
  constexpr bool Rational::gt(const Rational other) const {
    return normSign(*this) > normSign(other);
  }
  constexpr bool Rational::ge(const Rational other) const {
    return normSign(*this) >= normSign(other);;
  }
  
  constexpr Rational operator-(Rational &rat) {
    return {-rat.n, rat.d};
  }
  constexpr Rational &operator--(Rational &rat) {
    rat.n -= rat.d;
    return rat;
  }
  constexpr Rational &operator++(Rational &rat) {
    rat.n += rat.d;
    return rat;
  }
  constexpr Rational operator--(Rational &rat, int) {
    const Rational copy = rat;
    --rat;
    return copy;
  }
  constexpr Rational operator++(Rational &rat, int) {
    const Rational copy = rat;
    ++rat;
    return copy;
  }
  constexpr Rational operator+(const Rational a, const Rational b) {
    return {a.n * b.d + b.n * a.d, a.d * b.d};
  }
  constexpr Rational operator-(const Rational a, const Rational b) {
    return {a.n * b.d - b.n * a.d, a.d * b.d};
  }
  constexpr Rational operator*(const Rational a, const Rational b) {
    return {a.n * b.n, a.d * b.d};
  }
  constexpr Rational operator/(const Rational a, const Rational b) {
    return {a.n * b.d, a.d * b.n};
  }
  constexpr Rational operator%(const Rational a, const Rational b) {
    const Rational div = {a.n * b.d, a.d * b.n};
    return {b.n * (div.n % div.d), b.d * div.d};
  }
  constexpr Rational &operator+=(Rational &rat, const Rational other) {
    return rat = rat + other;
  }
  constexpr Rational &operator-=(Rational &rat, const Rational other) {
    return rat = rat - other;
  }
  constexpr Rational &operator*=(Rational &rat, const Rational other) {
    return rat = rat * other;
  }
  constexpr Rational &operator/=(Rational &rat, const Rational other) {
    return rat = rat / other;
  }
  constexpr Rational &operator%=(Rational &rat, const Rational other) {
    return rat = rat % other;
  }
  
  // 23/7 % 8/3 = 13/21
  static_assert((Rational{23, 7} % Rational{8, 3}).eq({13, 21}));
  static_assert((Rational{-23, -7} % Rational{8, 3}).eq({13, 21}));
  static_assert((Rational{23, 7} % Rational{-8, -3}).eq({13, 21}));
  static_assert((Rational{-23, -7} % Rational{-8, -3}).eq({13, 21}));
  
  // -23/7 % -8/3 = -13/21
  static_assert((Rational{-23, 7} % Rational{-8, 3}).eq({-13, 21}));
  static_assert((Rational{23, -7} % Rational{-8, 3}).eq({-13, 21}));
  static_assert((Rational{-23, 7} % Rational{8, -3}).eq({-13, 21}));
  static_assert((Rational{23, -7} % Rational{8, -3}).eq({-13, 21}));
  
  /*

  // 23/7 % -8/3 = -43/21
  static_assert((Rational{23, 7} % Rational{-8, 3}).eq({-43, 21}));
  static_assert((Rational{-23, -7} % Rational{-8, 3}).eq({-43, 21}));
  static_assert((Rational{23, 7} % Rational{8, -3}).eq({-43, 21}));
  static_assert((Rational{-23, -7} % Rational{8, -3}).eq({-43, 21}));
  
  // -23/7 % 8/3 = 43/21
  static_assert((Rational{-23, 7} % Rational{8, 3}).eq({43, 21}));
  static_assert((Rational{23, -7} % Rational{-8, -3}).eq({43, 21}));
  static_assert((Rational{-23, 7} % Rational{8, 3}).eq({43, 21}));
  static_assert((Rational{23, -7} % Rational{-8, -3}).eq({43, 21}));
  
  */
  
  constexpr Rational inv(const Rational rat) {
    return {rat.d, rat.n};
  }
  
  /// Set the denominator of the rational. Precision will be lost when the new
  /// denominator is not an integer multiple of the existing denominator
  constexpr Rational setDen(const Rational rat, const intmax_t newDen) {
    return {rat.n * newDen / rat.d, newDen};
  }
  
  static_assert(setDen({3, 4}, 100) == Rational{75, 100});
  
  /// Modify the given rationals so that they have the same denominator and
  /// return the new denominator
  constexpr intmax_t sameDen(Rational &a, Rational &b) {
    const intmax_t newDen = std::lcm(a.d, b.d);
    a = setDen(a, newDen);
    b = setDen(b, newDen);
    return newDen;
  }
}

#endif
