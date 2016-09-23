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
MOCK(write_swap(Register, Register))
MOCK(write_neg(Register))
MOCK(write_assign(Register, Register))
MOCK(write_assign(Register, i32))
MOCK(write_assign(Register, i64))
MOCK(write_add(Register, i32))
MOCK(write_add(Register, i8))
MOCK(write_sub(Register, i8))
MOCK(write_mul(Register, i8))
MOCK(write_div(Register, Register))
MOCK(write_mod(Register, Register))
MOCK(write_while_neq(Register, i8))
MOCK(write_if_eq(Register, i8))
MOCK(write_if_else_eq(Register, i8))
