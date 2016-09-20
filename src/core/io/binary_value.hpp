#pragma once

#include <core/typedefs.hpp>

#include <cstring>

template<int SIZE>
struct BinaryValue {
  template<class... ARGS>
  BinaryValue(ARGS... args) {
    build(0, args...);
  }

  const byte* get_bytes() const noexcept {
    return $bytes;
  }

  int get_len() const noexcept {
    return $len;
  }

private:
  byte $bytes[SIZE] = {0};
  int $len;

  void build(int pos) {
    $len = pos;
  }

  template<class HEAD, class... TAIL>
  void build(int pos, HEAD arg, TAIL... args) {
    push(pos, arg);
    build(pos + sizeof(HEAD), args...);
  }

  void push(long pos, byte x) {
    $bytes[pos] = x;
  }

  template<class T>
  void push(long pos, T x) {
    memcpy($bytes + pos, &x, sizeof(T));
  }
};
