#pragma once

#include <core/codegen/code_writer.hpp>

namespace x86_64 {
  class CodeWriter;
}

class x86_64::CodeWriter: public ::CodeWriter {
public:
  using ::CodeWriter::CodeWriter;

  void write_return() override;
  void write_return(Reg) override;

  void write_push(const Reg*, int count) override;
  void write_pop(const Reg*, int count) override;

  void write_neg(Reg) override;

  void write_swap(Reg, Reg) override;
  void write_swap(Mem, Mem) override;

  void write_assign(Reg, Imm) override;
  void write_assign(Reg dst, Reg src) override;
  void write_assign(Reg dst, Mem src) override;
  void write_assign(Mem dst, Reg src) override;
  void write_assign(Reg, DataReg) override;

  void write_add(Reg, Reg, Imm) override;
  void write_add(Reg, Reg, Reg) override;
  void write_add(Reg, Reg) override;
  void write_add(Reg, Mem) override;

  void write_sub(Reg, Imm) override;
  void write_sub(Reg, Reg) override;
  void write_sub(Reg, Mem) override;

  void write_mul(IntReg, Imm) override;
  void write_mul(IntReg, IntReg) override;

  void write_div(IntReg, IntReg) override;

  void write_mod(IntReg, IntReg) override;

  void write_bit_and(Reg dst, Reg src) override;

  void write_bit_or(Reg dst, Reg src) override;

  void write_shift_left(UintReg, u8 count) override;
  void write_shift_left(IntReg, u8 count) override;

  void write_shift_right(UintReg, u8 count) override;
  void write_shift_right(IntReg, u8 count) override;

  void write_while_neq(Reg, Imm) override;

  void write_if_eq(Reg, Imm) override;
  void write_if_else_eq(Reg, Imm) override;
};
