#include <core/codegen/code_writer.hpp>

#include <core/compile/compiler.hpp>

CodeWriter::CodeWriter(CodeBuf code_buf):
$output{code_buf} {}

void CodeWriter::set_compiler(Compiler* compiler) {
  $compiler = compiler;
}

Buf CodeWriter::get_buf() const noexcept {
  return $output.get_buf();
}

int CodeWriter::write_block() noexcept {
  int before = $output.get_len();
  $compiler->compile();
  int after = $output.get_len();

  return after - before;
}

#define MOCK(NAME_WITH_ARGS) \
  void CodeWriter::NAME_WITH_ARGS { \
    throw #NAME_WITH_ARGS " is unimplemented"; \
  }

MOCK(write_return())
MOCK(write_swap(RegIndex, RegIndex))
MOCK(write_neg(RegIndex))
MOCK(write_assign(RegIndex, RegIndex))
MOCK(write_assign(RegIndex, i32))
MOCK(write_assign(RegIndex, i64))
MOCK(write_add(RegIndex, i32))
MOCK(write_add(RegIndex, i8))
MOCK(write_sub(RegIndex, i8))
MOCK(write_while_neq(RegIndex, i8))
MOCK(write_if_eq(RegIndex, i8))
MOCK(write_if_else_eq(RegIndex, i8))
