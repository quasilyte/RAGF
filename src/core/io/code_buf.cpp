#include <core/io/code_buf.hpp>

#include <cstdlib>
#include <cstdio>

CodeBuf::CodeBuf(byte* data, i64 len, i64 cap):
$data{data}, $len{len}, $cap{cap} {}

CodeBuf::CodeBuf(Buf buf):
$data{buf.data}, $len{0}, $cap{buf.size} {}

Buf CodeBuf::get_buf() const noexcept {
  return Buf{$data, $len};
}

CodeBufSlice CodeBuf::preserve(int count) {
  if ($len + count >= $cap) {
    grow();
  }
  int offset = $len;
  $len += count;
  return CodeBufSlice{this, count, offset};
}

i64 CodeBuf::get_len() const noexcept {
  return $len;
}

void CodeBuf::write_byte(byte val) noexcept {
  if ($len + 1 >= $cap) {
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
