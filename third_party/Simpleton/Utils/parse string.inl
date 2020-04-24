//
//  parse string.inl
//  Simpleton Engine
//
//  Created by Indi Kernick on 30/9/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include <cerrno>
#include <cstring>
#include <cassert>
#include <functional>
#include "partial apply.hpp"

inline Utils::ParsingError::ParsingError(
  const LineCol<> lineCol
) : mLine(lineCol.line()),
    mCol(lineCol.col()) {}

inline unsigned Utils::ParsingError::line() const {
  return mLine;
}

inline unsigned Utils::ParsingError::column() const {
  return mCol;
}

inline Utils::ExpectChar::ExpectChar(
  const char c,
  const LineCol<> lineCol
) : ParsingError(lineCol), mExpected(c) {}

inline char Utils::ExpectChar::expectedChar() const {
  return mExpected;
}

inline const char *Utils::ExpectChar::what() const noexcept {
  //@TODO use static memory when std::to_chars arrives
  return (
    std::string("Expected character '")
    + mExpected
    + "' at "
    + std::to_string(mLine)
    + ':'
    + std::to_string(mCol)
  ).c_str();
}

template <size_t Size>
Utils::StackString<Size>::StackString(const std::string_view view) {
  size = view.size() < Size ? view.size() : Size;
  std::memcpy(data, view.data(), size);
}

template <size_t Size>
std::string_view Utils::StackString<Size>::view() const {
  return {data, size};
}

inline Utils::ExpectString::ExpectString(
  const std::string_view string,
  const LineCol<> lineCol
) : ParsingError{lineCol}, expected{string} {}

inline std::string_view Utils::ExpectString::expectedStr() const {
  return expected.view();
}

inline const char *Utils::ExpectString::what() const noexcept {
  //@TODO use static memory
  return (
    std::string("Expected string at ")
    + std::to_string(mLine)
    + ':'
    + std::to_string(mCol)
    + " \""
    + std::string(expected.view())
    + '"'
  ).c_str();
}

inline Utils::InvalidNumber::InvalidNumber(
  const std::errc error,
  const LineCol<> lineCol
) : ParsingError{lineCol}, mError{error} {}

inline std::errc Utils::InvalidNumber::error() const {
  return mError;
}

inline const char *Utils::InvalidNumber::what() const noexcept {
  //@TODO use static memory when std::to_chars arrives
  return (
    std::string("Expected number at ")
    + std::to_string(mLine)
    + ':'
    + std::to_string(mCol)
    + " \""
    + std::make_error_code(mError).message()
    + '"'
  ).c_str();
}

inline Utils::InvalidEnum::InvalidEnum(
  const std::string_view name,
  const LineCol<> lineCol
) : ParsingError{lineCol}, nameStr{name} {}

inline std::string_view Utils::InvalidEnum::name() const {
  return nameStr.view();
}

inline const char *Utils::InvalidEnum::what() const noexcept {
  //@TODO use static memory
  return (
    std::string("Expected enumeration at ")
    + std::to_string(mLine)
    + ':'
    + std::to_string(mCol)
    + " No matching enumeration for \""
    + std::string(nameStr.view())
    + '"'
  ).c_str();
}

inline Utils::ParseString::ParseString(const std::string &string)
  : beg{string.data()}, end{string.data() + string.size()} {}

inline Utils::ParseString::ParseString(const std::string_view view)
  : beg{view.data()}, end{view.data() + view.size()} {
  throwIfNull(view.data());
}

inline Utils::ParseString::ParseString(const char *const data, const size_t size)
  : beg{data}, end{data + size} {
  throwIfNull(data);
}

inline const char *Utils::ParseString::data() const {
  return beg;
}

inline size_t Utils::ParseString::size() const {
  assert(beg <= end);
  return static_cast<size_t>(end - beg);
}

inline Utils::LineCol<> Utils::ParseString::lineCol() const {
  return pos;
}

inline Utils::LineCol<>::Line Utils::ParseString::line() const {
  return pos.line();
}

inline Utils::LineCol<>::Col Utils::ParseString::col() const {
  return pos.col();
}

inline std::string_view Utils::ParseString::view() const {
  return {beg, size()};
}

inline std::string_view Utils::ParseString::view(const size_t numChars) const {
  return {beg, minSize(numChars)};
}

inline bool Utils::ParseString::empty() const {
  return beg == end;
}

inline char Utils::ParseString::operator[](const size_t i) const {
  return beg[i];
}

inline char Utils::ParseString::at(const size_t i) const {
  const char *const ptr = beg + i;
  if (ptr >= end) {
    throw std::out_of_range("Index on parse string out of range");
  }
  return *ptr;
}

inline char Utils::ParseString::front() const {
  return *beg;
}

inline Utils::ParseString &Utils::ParseString::advance(const size_t numChars) {
  if (beg + numChars > end) {
    throw std::out_of_range("Advanced parse string too many characters");
  }
  advanceNoCheck(numChars);
  return *this;
}

inline Utils::ParseString &Utils::ParseString::advance() {
  if (beg + 1 > end) {
    throw std::out_of_range("Advanced parse string too many characters");
  }
  advanceNoCheck();
  return *this;
}

inline Utils::ParseString &Utils::ParseString::skip(const char c) {
  skip(equal_to(c));
  return *this;
}

template <typename Pred>
Utils::ParseString &Utils::ParseString::skip(Pred &&pred) {
  while (beg < end && pred(*beg)) {
    advanceNoCheck();
  }
  return *this;
}

inline Utils::ParseString &Utils::ParseString::skipWhitespace() {
  return skip(isspace);
}

inline Utils::ParseString &Utils::ParseString::skipUntil(const char c) {
  return skipUntil(equal_to(c));
}

template <typename Pred>
Utils::ParseString &Utils::ParseString::skipUntil(Pred &&pred) {
  return skip(std::not_fn(pred));
}

inline Utils::ParseString &Utils::ParseString::skipUntilWhitespace() {
  return skipUntil(isspace);
}

inline Utils::ParseString &Utils::ParseString::expect(const char c) {
  if (empty() || *beg != c) {
    throw ExpectChar(c, pos);
  }
  advanceNoCheck();
  return *this;
}

inline Utils::ParseString &Utils::ParseString::expect(const char *data, const size_t bufSize) {
  if (size() < bufSize || std::memcmp(beg, data, bufSize) != 0) {
    throw ExpectString({data, bufSize}, pos);
  }
  advanceNoCheck(bufSize);
  return *this;
}

inline Utils::ParseString &Utils::ParseString::expect(const std::string_view view) {
  return expect(view.data(), view.size());
}

inline char Utils::ParseString::expectEither(const char a, const char b) {
  const char curr = *beg;
  if (empty() || (curr != a && curr != b)) {
    // @TODO dedicated exception?
    throw ExpectChar(a, pos);
  }
  advanceNoCheck();
  return curr;
}

inline std::string_view Utils::ParseString::expectEither(
  const std::string_view a,
  const std::string_view b
) {
  if (check(a)) return a;
  if (check(b)) return b;
  // @TODO dedicated exception?
  throw ExpectString(a, pos);
}

template <typename Pred>
inline Utils::ParseString &Utils::ParseString::expectAfter(const char c, Pred &&pred) {
  return skip(pred).expect(c);
}

inline Utils::ParseString &Utils::ParseString::expectAfterWhitespace(const char c) {
  return skipWhitespace().expect(c);
}

inline bool Utils::ParseString::check(const char c) {
  if (empty() || *beg != c) {
    return false;
  } else {
    advanceNoCheck();
    return true;
  }
}

inline bool Utils::ParseString::check(const char *data, const size_t size) {
  if (size == 0) {
    return true;
  }
  if (end < beg + size) {
    return false;
  }
  if (std::memcmp(beg, data, size) == 0) {
    advanceNoCheck(size);
    return true;
  } else {
    return false;
  }
}

inline bool Utils::ParseString::check(const std::string_view view) {
  return check(view.data(), view.size());
}

template <size_t SIZE>
bool Utils::ParseString::check(const char (&string)[SIZE]) {
  return check(string, SIZE - 1);
}

template <typename Pred>
bool Utils::ParseString::check(Pred &&pred) {
  if (empty() || !pred(*beg)) {
    return false;
  } else {
    advanceNoCheck();
    return true;
  }
}

inline bool Utils::ParseString::checkAnyChar(const char *data, const size_t size) {
  return checkAnyChar({data, size});
}

inline bool Utils::ParseString::checkAnyChar(const std::string_view str) {
  if (empty()) {
    return false;
  }
  for (const char c : str) {
    if (c == *beg) {
      advanceNoCheck();
      return true;
    }
  }
  return false;
}

template <typename Number>
std::errc Utils::ParseString::tryParseNumber(Number &number) {
  errno = 0;
  if constexpr (std::is_integral<Number>::value) {
    if constexpr (std::is_unsigned<Number>::value) {
      char *numEnd;
      const unsigned long long num = std::strtoull(beg, &numEnd, 0);
      if (errno == ERANGE || num > std::numeric_limits<Number>::max()) {
        errno = 0;
        return std::errc::result_out_of_range;
      }
      if (num == 0 && numEnd == beg) {
        return std::errc::invalid_argument;
      }
      assert(beg < numEnd);
      advanceNoCheck(static_cast<size_t>(numEnd - beg));
      number = static_cast<Number>(num);
    } else if constexpr (std::is_signed<Number>::value) {
      char *numEnd;
      const long long num = std::strtoll(beg, &numEnd, 0);
      if (errno == ERANGE || num < std::numeric_limits<Number>::lowest() || num > std::numeric_limits<Number>::max()) {
        errno = 0;
        return std::errc::result_out_of_range;
      }
      if (num == 0 && numEnd == beg) {
        return std::errc::invalid_argument;
      }
      assert(beg < numEnd);
      advanceNoCheck(static_cast<size_t>(numEnd - beg));
      number = static_cast<Number>(num);
    }
  } else if constexpr (std::is_floating_point<Number>::value) {
    char *numEnd;
    const long double num = std::strtold(beg, &numEnd);
    if (errno == ERANGE || num < std::numeric_limits<Number>::lowest() || num > std::numeric_limits<Number>::max()) {
      errno = 0;
      return std::errc::result_out_of_range;
    }
    if (num == 0 && numEnd == beg) {
      return std::errc::invalid_argument;
    }
    assert(beg < numEnd);
    advanceNoCheck(static_cast<size_t>(numEnd - beg));
    number = static_cast<Number>(num);
  }
  
  return std::errc{};
  
  /*
  @TODO std::from_chars
  
  const auto [end, ec] = std::from_chars(mData, mData + mSize, number);
  if (ec == std::errc{}) {
    advanceNoCheck(end - mData);
  }
  return error;
  */
}

template <typename Number>
Utils::ParseString &Utils::ParseString::parseNumber(Number &number) {
  const std::errc error = tryParseNumber(number);
  if (error != std::errc{}) {
    throw InvalidNumber(error, pos);
  }
  return *this;
}

template <typename Number>
Number Utils::ParseString::parseNumber() {
  Number number;
  parseNumber(number);
  return number;
}

inline size_t Utils::ParseString::tryParseEnum(
  const std::string_view *const names,
  const size_t numNames
) {
  throwIfNull(names);
  const std::string_view *const namesEnd = names + numNames;
  for (const std::string_view *n = names; n != namesEnd; ++n) {
    if (check(*n)) {
      return static_cast<size_t>(n - names);
    }
  }
  return numNames;
}

template <typename Enum>
Enum Utils::ParseString::parseEnum(
  const std::string_view *const names,
  const size_t numNames
) {
  const size_t index = tryParseEnum(names, numNames);
  if (index == numNames) {
    throw InvalidEnum(view(), pos);
  }
  return static_cast<Enum>(index);
}

template <typename Pred>
size_t Utils::ParseString::tryParseEnum(
  const std::string_view *const names,
  const size_t numNames,
  Pred &&pred
) {
  throwIfNull(names);
  const std::string_view *const namesEnd = names + numNames;
  for (const std::string_view *n = names; n != namesEnd; ++n) {
    if (end < beg + n->size()) {
      continue;
    }
    if (n->size() == 0 && (beg == end || pred(*beg))) {
      return static_cast<size_t>(n - names);
    }
    if (beg + n->size() == end || pred(beg[n->size()])) {
      if (std::memcmp(beg, n->data(), n->size()) == 0) {
        advanceNoCheck(n->size());
        return static_cast<size_t>(n - names);
      }
    }
  }
  return numNames;
}

template <typename Enum, typename Pred>
Enum Utils::ParseString::parseEnum(
  const std::string_view *const names,
  const size_t numNames,
  Pred &&pred
) {
  const size_t index = tryParseEnum(names, numNames, std::forward<Pred>(pred));
  if (index == numNames) {
    throw InvalidEnum(view(), pos);
  }
  return static_cast<Enum>(index);
}

inline size_t Utils::ParseString::copy(char *const dst, const size_t dstSize) {
  throwIfNull(dst);
  const size_t numChars = minSize(dstSize);
  std::memcpy(dst, beg, numChars);
  advanceNoCheck(numChars);
  return numChars;
}

inline Utils::ParseString &Utils::ParseString::copy(std::string &dst, const size_t copySize) {
  const size_t numChars = minSize(copySize);
  dst.append(beg, numChars);
  advanceNoCheck(numChars);
  return *this;
}

template <typename Pred>
size_t Utils::ParseString::copyWhile(char *dst, const size_t dstSize, Pred &&pred) {
  throwIfNull(dst);
  size_t numChars = 0;
  const size_t maxChars = minSize(dstSize);
  while (numChars < maxChars && pred(*beg)) {
    *dst = *beg;
    ++dst;
    advanceNoCheck(); // increments mData
    ++numChars;
  }
  return numChars;
}

template <typename Pred>
Utils::ParseString &Utils::ParseString::copyWhile(std::string &dst, Pred &&pred) {
  while (!empty() && pred(*beg)) {
    dst.push_back(*beg);
    advanceNoCheck();
  }
  return *this;
}

inline size_t Utils::ParseString::copyUntil(char *const dst, const size_t dstSize, const char c) {
  return copyUntil(dst, dstSize, equal_to(c));
}

inline Utils::ParseString &Utils::ParseString::copyUntil(std::string &dst, const char c) {
  return copyUntil(dst, equal_to(c));
}

template <typename Pred>
size_t Utils::ParseString::copyUntil(char *const dst, const size_t dstSize, Pred &&pred) {
  return copyWhile(dst, dstSize, std::not_fn(pred));
}

template <typename Pred>
Utils::ParseString &Utils::ParseString::copyUntil(std::string &dst, Pred &&pred) {
  return copyWhile(dst, std::not_fn(pred));
}

inline size_t Utils::ParseString::copyUntilWhitespace(char *const dst, const size_t dstSize) {
  return copyUntil(dst, dstSize, isspace);
}

inline Utils::ParseString &Utils::ParseString::copyUntilWhitespace(std::string &dst) {
  return copyUntil(dst, isspace);
}

inline std::string_view Utils::ParseString::beginViewing() const {
  return {beg, 0};
}

inline void Utils::ParseString::endViewing(std::string_view &view) const {
  view = {view.data(), static_cast<size_t>(beg - view.data())};
}

inline void Utils::ParseString::advanceNoCheck(const size_t numChars) {
  pos.putString(beg, numChars);
  beg += numChars;
}

inline void Utils::ParseString::advanceNoCheck() {
  pos.putChar(*beg);
  ++beg;
}

inline size_t Utils::ParseString::minSize(const size_t otherSize) const {
  const size_t thisSize = size();
  return thisSize < otherSize ? thisSize : otherSize;
}
