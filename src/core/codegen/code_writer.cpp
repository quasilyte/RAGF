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
MOCK(write_swap(Reg, Reg))
MOCK(write_neg(Reg))
MOCK(write_assign(Reg, Reg))
MOCK(write_assign(Reg, i32))
MOCK(write_assign(Reg, i64))
MOCK(write_assign(Reg, Mem64))
MOCK(write_assign(Reg, DataReg))
MOCK(write_add(Reg, i32))
MOCK(write_add(Reg, i8))
MOCK(write_add(Reg, Reg))
MOCK(write_sub(Reg, i8))
MOCK(write_mul(IntReg, i8))
MOCK(write_div(IntReg, IntReg))
MOCK(write_mod(IntReg, IntReg))
MOCK(write_shift_left(UintReg, u8))
MOCK(write_shift_left(IntReg, u8))
MOCK(write_shift_right(UintReg, u8))
MOCK(write_shift_right(IntReg, u8))
MOCK(write_bit_and(Reg, Reg))
MOCK(write_bit_or(Reg, Reg))
MOCK(write_while_neq(Reg, i8))
MOCK(write_if_eq(Reg, i8))
MOCK(write_if_else_eq(Reg, i8))
