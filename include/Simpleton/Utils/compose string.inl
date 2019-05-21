//
//  compose string.inl
//  Simpleton Engine
//
//  Created by Indi Kernick on 22/2/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

inline Utils::ComposeString::ComposeString(const size_t capacity)
  : string{std::make_unique<char []>(capacity)}, length{0}, capacity{capacity} {
  sepStack.reserve(CHAR_BIT);
}

inline const char *Utils::ComposeString::data() const {
  return string.get();
}

inline size_t Utils::ComposeString::size() const {
  return length;
}

inline char *Utils::ComposeString::begin() {
  return string.get();
}

inline char *Utils::ComposeString::curr() {
  return string.get() + length;
}

inline char *Utils::ComposeString::end() {
  return string.get() + capacity;
}

inline std::string_view Utils::ComposeString::view() const {
  return {string.get(), length};
}

inline size_t Utils::ComposeString::freeSpace() const {
  return capacity - length;
}

inline void Utils::ComposeString::reserve(const size_t newCap) {
  if (newCap > capacity) {
    setCapacity(newCap);
  }
}

inline void Utils::ComposeString::reserveToFit(const size_t extra) {
  if (length + extra > capacity) {
    setCapacity((capacity + extra) * 2);
  }
}

inline void Utils::ComposeString::addSize(const size_t extra) {
  length += extra;
}

inline bool Utils::ComposeString::empty() const {
  return length == 0;
}

inline void Utils::ComposeString::write(const char c) {
  if (length == capacity) {
    setCapacity((capacity + 1) * 2);
  }
  *curr() = c;
  ++length;
}

inline void Utils::ComposeString::write(const std::string_view view) {
  reserveToFit(view.size());
  std::memcpy(curr(), view.data(), view.size());
  length += view.size();
}

template <size_t Size>
void Utils::ComposeString::write(const char (&str)[Size]) {
  if constexpr (Size == 2) {
    write(str[0]);
  } else {
    write({&str[0], Size - 1});
  }
}

template <typename Number>
void Utils::ComposeString::writeNumber(const Number num) {
  write(std::to_string(num));
  /*
  @TODO
  
  reserveToFit(64);
  const auto [ptr, ec] = std::to_chars(curr(), end(), num);
  if (!ec) {
    length = ptr - string.get();
  }
  */
}
        
template <typename Enum>
void Utils::ComposeString::writeEnum(const Enum e, const std::string_view *names) {
  write(names[static_cast<size_t>(e)]);
}

template <typename String>
void Utils::ComposeString::open(String &&str) {
  open();
  write(std::forward<String>(str));
}

inline void Utils::ComposeString::open() {
  sepStack.push_back(false);
}

template <typename String>
void Utils::ComposeString::separate(String &&str) {
  if (separate()) {
    write(std::forward<String>(str));
  }
}

inline bool Utils::ComposeString::separate() {
  // Can't use std::exchange because of std::vector<bool>
  // :-(
  // There should have been a separate container called std::dynamic_bitset
  const bool sep = sepStack.back();
  sepStack.back() = true;
  return sep;
}

template <typename String>
void Utils::ComposeString::close(String &&str) {
  close();
  write(std::forward<String>(str));
}

inline void Utils::ComposeString::close() {
  sepStack.pop_back();
}

inline void Utils::ComposeString::setCapacity(const size_t newCap) {
  auto newStr = std::make_unique<char []>(newCap);
  std::memcpy(newStr.get(), string.get(), length);
  string = std::move(newStr);
  capacity = newCap;
}
