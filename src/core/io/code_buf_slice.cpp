#include <core/io/code_buf_slice.hpp>

#include <core/io/code_buf.hpp>

CodeBufSlice::CodeBufSlice(CodeBuf* origin, int size, int offset):
$origin{origin}, $size{size}, $offset{offset} {}

CodeBufSlice::operator CodeBuf*() const noexcept {
  static CodeBuf code_buf{nullptr, 0, 0};

  byte* data = $origin->$data + $offset;
  i64 len = 0;
  i64 cap = $size + 1;

  code_buf.$data = data;
  code_buf.$len = len;
  code_buf.$cap = cap;

  return &code_buf;
}
