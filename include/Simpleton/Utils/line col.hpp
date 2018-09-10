//
//  line col.hpp
//  Simpleton Engine
//
//  Created by Indi Kernick on 25/2/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_utils_line_col_hpp
#define engine_utils_line_col_hpp

#include <cctype>
#include <string>
#include "null check.hpp"

namespace Utils {
  ///Keeps track of lines and columns in text.
  ///Great for writing error messages in parsers
  template <
    typename Line_ = uint32_t,
    typename Col_ = uint32_t,
    Col_ SIZE_OF_TAB_ = 8,
    Line_ FIRST_LINE_ = 1,
    Col_ FIRST_COL_ = 1
  >
  class LineCol {
  public:
    using Line = Line_;
    using Col = Col_;
    
    static constexpr Col  SIZE_OF_TAB = SIZE_OF_TAB_;
    static constexpr Line FIRST_LINE  = FIRST_LINE_;
    static constexpr Col  FIRST_COL   = FIRST_COL_;
    
    // 3.9 lines and 18.4 columns doesn't make any sense!
    static_assert(std::is_integral_v<Line>, "Type of line must be an integer");
    static_assert(std::is_integral_v<Col>, "Type of column must be an integer");
  
    LineCol()
      : mLine(FIRST_LINE), mCol(FIRST_COL) {}
    LineCol(const Line line, const Col col)
      : mLine(line), mCol(col) {
      assert(line >= FIRST_LINE);
      assert(col >= FIRST_COL);
    }
    
    ///Move line and col according to the char
    void putChar(const char c) {
      switch (c) {
        case '\t':
          //assumes that Col is an integer
          mCol = (mCol + SIZE_OF_TAB - 1) / SIZE_OF_TAB * SIZE_OF_TAB;
          break;
        case '\n':
          ++mLine;
          mCol = FIRST_COL;
          break;
        case '\v':
        case '\f':
          ++mLine;
          break;
        case '\r':
          mCol = FIRST_COL;
          break;
        case '\b':
          if (mCol != FIRST_COL) {
            --mCol;
          }
          break;
        
        default:
          if (std::isprint(c)) {
            ++mCol;
          }
      }
    }
    ///Call putChar(char) for the first n chars in the string
    void putString(const char *str, size_t size) {
      throwIfNull(str);
      while (size) {
        putChar(*str);
        ++str;
        --size;
      }
    }
    ///Sets line to FIRST_LINE and col to FIRST_COL
    void reset() {
      mLine = FIRST_LINE;
      mCol = FIRST_COL;
    }
    
    ///Sets line and col
    void moveTo(const Line newLine, const Col newCol) {
      mLine = newLine;
      mCol = newCol;
    }
    ///Adds line and col
    void moveBy(const Line deltaLine, const Col deltaCol) {
      mLine += deltaLine;
      mCol += deltaCol;
    }
    
    LineCol &operator+=(const LineCol other) {
      mLine += other.mLine;
      mCol += other.mCol;
      return *this;
    }
    LineCol &operator-=(const LineCol other) {
      mLine -= other.mLine;
      mCol -= other.mCol;
      return *this;
    }
    LineCol operator+(const LineCol other) const {
      return {
        mLine + other.mLine,
        mCol + other.mCol
      };
    }
    LineCol operator-(const LineCol other) const {
      return {
        mLine - other.mLine,
        mCol - other.mCol
      };
    }
    
    Line line() const {
      return mLine;
    }
    Col col() const {
      return mCol;
    }
    
    const char *asStr() const {
      //The largest 64 bit unsigned integer value is 18446744073709551615 which is
      //20 characters. 20 + ':' + 20 + '\0' = 42 = the answer to the ultimate question
      static char str[42];
      
      std::string numString = std::to_string(mLine);
      std::copy(numString.cbegin(), numString.cend(), str);
      size_t lineStrSize = numString.size();
      str[lineStrSize] = ':';
      numString = std::to_string(mCol);
      std::copy(numString.cbegin(), numString.cend(), str + lineStrSize + 1);
      str[lineStrSize + 1 + numString.size()] = 0;
      
      /*
      @TODO uncomment
      
      const auto [end, error] = std::to_chars(str, str + 42, line);
      if (error) {
        throw std::runtime_error(error.message());
      }
      *end = ':';
      const auto [end1, error1] = std::to_chars(end + 1, str + 42, col);
      if (error1) {
        throw std::runtime_error(error1.message());
      }*/
      
      return str;
    }
    
  private:
    Line mLine;
    Col mCol;
  };
}

#endif
