#pragma once

#include <core/typedefs.hpp>
#include <core/io/binary_value.hpp>

class CodeBuf {
public:
  CodeBuf();

  void set_buf(Buf) noexcept;
  Buf get_buf() const noexcept;

  void set_len(int) noexcept;
  int get_len() const noexcept;

  void write_byte(byte) noexcept;
  void write_bytes(const byte* bytes, int count) noexcept;

  template<class T>
  int write(T bytes_provider) noexcept {
    write_bytes(bytes_provider.get_bytes(), bytes_provider.get_len());
    return bytes_provider.get_len();
  }

private:
  byte* $data;
  int $len;
  int $cap;

  void grow();
};
