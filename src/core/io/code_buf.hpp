#pragma once

#include <core/typedefs.hpp>
#include <core/io/binary_value.hpp>

#include <vector>

class CodeBuf {
public:
  CodeBuf();

  Buf get_buf() const noexcept;

  void write_byte(byte) noexcept;

  void write_bytes(const byte* bytes, int count) noexcept;

  template<class T>
  void write(T bytes_provider) noexcept {
    write_bytes(bytes_provider.get_bytes(), bytes_provider.get_len());
  }

private:
  std::vector<byte> $data;
};
