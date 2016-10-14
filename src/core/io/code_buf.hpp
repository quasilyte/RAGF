#pragma once

#include <core/typedefs.hpp>
#include <core/io/binary_value.hpp>
#include <core/io/code_buf_slice.hpp>
#include <cstdio>
class CodeBuf {
public:
  CodeBuf(byte* data, i64 len, i64 cap);
  CodeBuf(Buf);

  Buf get_buf() const noexcept;

  CodeBufSlice preserve(int count);

  i64 get_len() const noexcept;

  void write_byte(byte) noexcept;
  void write_bytes(const byte* bytes, int count) noexcept;

//  template<class T>
//  void write(T bytes_provider) noexcept {
//    write_bytes(bytes_provider.get_bytes(), bytes_provider.get_len());
//  }

  CodeBuf& operator<<(byte val) {
    write_byte(val);
    return *this;
  }

  template<class T>
  CodeBuf& operator<<(T bytes_provider) noexcept {
    write_bytes(bytes_provider.get_bytes(), bytes_provider.get_len());
    return *this;
  }

private:
  byte* $data;
  i64 $len;
  i64 $cap;

  void grow();

  friend class CodeBufSlice;
};
