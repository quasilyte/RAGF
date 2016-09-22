#include <core/io/code_buf_slice.hpp>

#include <core/io/code_buf.hpp>

CodeBufSlice::CodeBufSlice(CodeBuf* origin, int size, int offset):
$origin{origin}, $size{size}, $offset{offset} {}

CodeBufSlice::operator CodeBuf() const noexcept {
  byte* data = $origin->$data + $offset;
  i64 len = 0;
  i64 cap = $size + 1;
  return CodeBuf{data, len, cap};
}
