#include <core/io/code_buf.hpp>

#include <cstdlib>
#include <cstdio>

CodeBuf::CodeBuf(Buf buf):
$data{buf.data}, $len{0}, $cap{buf.size} {}

Buf CodeBuf::get_buf() const noexcept {
  return Buf{$data, $len};
}

void CodeBuf::set_len(i64 len) noexcept {
  $len = len;
}

i64 CodeBuf::get_len() const noexcept {
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
