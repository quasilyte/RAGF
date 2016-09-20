#include <core/io/code_buf.hpp>

CodeBuf::CodeBuf() {
  $data.reserve(64);
}

Buf CodeBuf::get_buf() const noexcept {
  return Buf{$data.data(), static_cast<i64>($data.size())};
}

void CodeBuf::write_byte(byte val) noexcept {
  $data.push_back(val);
}

void CodeBuf::write_bytes(const byte* bytes, int count) noexcept {
  $data.insert($data.end(), bytes, bytes + count);
}
