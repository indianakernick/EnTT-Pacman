//
//  atom.hpp
//  Simpleton Engine
//
//  Created by Indi Kernick on 7/9/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#ifndef engine_utils_atom_hpp
#define engine_utils_atom_hpp

#include <cstdint>
#include <stdexcept>

namespace Utils {
  using AtomInt = uint64_t;
  
  struct Atom {
    static constexpr size_t bits = 5;
    static constexpr size_t digits = 64 / bits;
    static constexpr AtomInt digit_mask = (1 << bits) - 1;
    
    struct char_array {
      constexpr explicit char_array()
        : data{} {}
      
      constexpr const char *str() const noexcept {
        return data;
      }
      static constexpr size_t size() noexcept {
        return digits;
      }
      constexpr char &operator[](const size_t index) noexcept {
        return data[index];
      }
      constexpr char operator[](const size_t index) const noexcept {
        return data[index];
      }
      
    private:
      char data[digits + 1];
    };
  
    constexpr explicit Atom(const AtomInt value)
      : value{value} {}
    
    constexpr operator AtomInt() const noexcept {
      return value;
    }
    
  private:
    AtomInt value;
  };

  namespace detail {
    constexpr AtomInt no = ~AtomInt{};
    
    constexpr AtomInt to_atom[128] {
  //  32 special characters
      0,no,no,no,no,no,no,no,no,no,no,no,no,no,no,no,
     no,no,no,no,no,no,no,no,no,no,no,no,no,no,no,no,
  //     !  "  #  $  %  &  '  (  )  *  +  ,  -  .  /
     no,no,no,27,no,no,no,no,no,no,no,no,no,no,28,29,
  //  0  1  2  3  4  5  6  7  8  9  :  ;  <  =  >  ?
     no,no,no,no,no,no,no,no,no,no,no,no,no,no,no,no,
  //  @  A  B  C  D  E  F  G  H  I  J  K  L  M  N  O
     30, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,11,12,13,14,15,
  //  P  Q  R  S  T  U  V  W  X  Y  Z  [  \  ]  ^  _
     16,17,18,19,20,21,22,23,24,25,26,no,no,no,no,31,
  //  `  a  b  c  d  e  f  g  h  i  j  k  l  m  n  o
     no, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14,15,
  //  p  q  r  s  t  u  v  w  x  y  z  {  |  }  ~  DEL
     16,17,18,19,20,21,22,23,24,25,26,no,no,no,no,no,
    };
    
    constexpr char from_atom[(1 << Atom::bits) + 1] {"\0abcdefghijklmnopqrstuvwxyz#./@_"};
  }

  constexpr Atom toAtom(const char *data, const size_t size) {
    AtomInt set = 0;
    if (size > Atom::digits) {
      throw std::runtime_error("String too long");
    }
    for (AtomInt index = 0; index != size; ++index) {
      const size_t tableIndex = data[index];
      const AtomInt code = detail::to_atom[tableIndex];
      if (code == detail::no) {
        throw std::runtime_error("Invalid character in string");
      }
      set |= code << (index * Atom::bits);
    }
    return Atom{set};
  }

  constexpr Atom::char_array fromAtom(const Atom atom) noexcept {
    Atom::char_array array;
    AtomInt set = atom;
    for (size_t index = 0; index != Atom::digits; ++index) {
      const AtomInt code = set & Atom::digit_mask;
      array[index] = detail::from_atom[code];
      set >>= Atom::bits;
    }
    return array;
  }
  
  namespace Literals {
    constexpr Atom operator""_atom(const char *data, const size_t size) noexcept {
      return toAtom(data, size);
    }
    
    static_assert(""_atom == 0);
    static_assert("a"_atom == 1);
    static_assert("aa"_atom == 33);
    static_assert("abcdefghijkl"_atom == 445092485129178177);
    
    static_assert(fromAtom(""_atom)[0] == 0);
    
    static_assert(fromAtom("a"_atom)[0] == 'a');
    static_assert(fromAtom("a"_atom)[1] == 0  );
    
    static_assert(fromAtom("aa"_atom)[0] == 'a');
    static_assert(fromAtom("aa"_atom)[1] == 'a');
    static_assert(fromAtom("aa"_atom)[2] == 0  );
    
    static_assert(fromAtom("abcdefghijkl"_atom)[ 0] == 'a');
    static_assert(fromAtom("abcdefghijkl"_atom)[ 1] == 'b');
    static_assert(fromAtom("abcdefghijkl"_atom)[ 2] == 'c');
    static_assert(fromAtom("abcdefghijkl"_atom)[ 3] == 'd');
    static_assert(fromAtom("abcdefghijkl"_atom)[ 4] == 'e');
    static_assert(fromAtom("abcdefghijkl"_atom)[ 5] == 'f');
    static_assert(fromAtom("abcdefghijkl"_atom)[ 6] == 'g');
    static_assert(fromAtom("abcdefghijkl"_atom)[ 7] == 'h');
    static_assert(fromAtom("abcdefghijkl"_atom)[ 8] == 'i');
    static_assert(fromAtom("abcdefghijkl"_atom)[ 9] == 'j');
    static_assert(fromAtom("abcdefghijkl"_atom)[10] == 'k');
    static_assert(fromAtom("abcdefghijkl"_atom)[11] == 'l');
    static_assert(fromAtom("abcdefghijkl"_atom)[12] == 0  );
  }
}

#endif
