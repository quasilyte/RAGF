#include <core/io/code_buf.hpp>

#include <cstdlib>
#include <cstdio>

CodeBuf::CodeBuf(): $len{0}, $cap{0} {}

void CodeBuf::set_buf(Buf buf) noexcept {
  $data = buf.data;
  $cap = buf.size;
}

Buf CodeBuf::get_buf() const noexcept {
  return Buf{$data, $len};
}

void CodeBuf::set_len(int len) noexcept {
  $len = len;
}

int CodeBuf::get_len() const noexcept {
  return $len;
}

void CodeBuf::write_byte(byte val) noexcept {
  if ($len + 1 > $cap) {
    grow();
  }
  $data[$len] = val;
  $len += 1;
}

void CodeBuf::write_bytes(const byte* bytes, int count) noexcept {
  if ($len + count >= $cap) {
    grow();
  }
  memcpy($data + $len, bytes, count);
  $len += count;
}

void CodeBuf::grow() {
  $cap *= 2;
  $data = static_cast<byte*>(realloc($data, $cap));
}
