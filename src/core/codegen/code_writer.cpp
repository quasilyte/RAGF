#include <core/codegen/code_writer.hpp>

CodeWriter::CodeWriter() {}

void CodeWriter::set_code_buf(CodeBuf* code_buf) noexcept {
  $output = code_buf;
}

Buf CodeWriter::get_buf() const noexcept {
  return $output->get_buf();
}

void CodeWriter::write_block(Buf block) noexcept {
  $output->write_bytes(block.data, block.size);
}

#define MOCK(NAME_WITH_ARGS) \
  void CodeWriter::NAME_WITH_ARGS { \
    throw #NAME_WITH_ARGS ": unimplemented"; \
  }

MOCK(write_return())
MOCK(write_swap(RegIndex, RegIndex))
MOCK(write_neg(RegIndex))
MOCK(write_assign(RegIndex, i32))
MOCK(write_assign(RegIndex, i64))
MOCK(write_add(RegIndex, i32))
MOCK(write_add(RegIndex, i8))
MOCK(write_sub(RegIndex, i8))
MOCK(write_loop(i32))
MOCK(write_while_neq(i32, RegIndex, i8))
