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
MOCK(write_return(Reg))

MOCK(write_push(const Reg*, int))
MOCK(write_pop(const Reg*, int))

MOCK(write_swap(Reg, Reg))
MOCK(write_swap(PtrReg, PtrReg))

MOCK(write_neg(Reg))

MOCK(write_assign(Reg, Reg))
MOCK(write_assign(Reg, Imm))
MOCK(write_assign(Reg, PtrReg))
MOCK(write_assign(PtrReg, Reg))
MOCK(write_assign(Reg, DataReg))

MOCK(write_add(Reg, Reg, Imm))
MOCK(write_add(Reg, Reg, Reg))
MOCK(write_add(Reg, PtrReg))

MOCK(write_sub(Reg, Reg, Imm))
MOCK(write_sub(Reg, Reg, Reg))
MOCK(write_sub(Reg, PtrReg))

MOCK(write_mul(IntReg, Imm))
MOCK(write_mul(IntReg, IntReg))

MOCK(write_div(IntReg, IntReg))
MOCK(write_mod(IntReg, IntReg))
MOCK(write_shift_left(UintReg, u8))
MOCK(write_shift_left(IntReg, u8))
MOCK(write_shift_right(UintReg, u8))
MOCK(write_shift_right(IntReg, u8))
MOCK(write_bit_and(Reg, Reg))
MOCK(write_bit_or(Reg, Reg))

MOCK(write_while_neq(Reg, Imm))

MOCK(write_if_eq(Reg, Imm))
MOCK(write_if_else_eq(Reg, Imm))
