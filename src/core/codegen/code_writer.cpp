#include <core/codegen/code_writer.hpp>

CodeWriter::CodeWriter() {}

Buf CodeWriter::get_buf() const noexcept {
  return $output.get_buf();
}

#define MOCK(NAME_WITH_ARGS) \
  void CodeWriter::NAME_WITH_ARGS { \
    throw #NAME_WITH_ARGS ": unimplemented"; \
  }

MOCK(write_return())
MOCK(write_swap(RegIndex, RegIndex))
MOCK(write_assign(RegIndex, i32))
MOCK(write_assign(RegIndex, i64))
MOCK(write_add(RegIndex, i32))
