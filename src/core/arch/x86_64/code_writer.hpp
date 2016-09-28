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

  void write_assign(Reg, i32) override;
  void write_assign(Reg, i64) override;
  void write_assign(Reg dst, Reg src) override;
  void write_assign(Reg, Mem64, i8) override;
  void write_assign(Mem64, Reg, i8) override;
  void write_assign(Reg, DataReg) override;

  void write_add(Reg, i8) override;
  void write_add(Reg, i32) override;
  void write_add(Reg, Reg) override;
  void write_add(Reg, Mem64) override;

  void write_sub(Reg, i8) override;
  void write_sub(Reg, i32) override;
  void write_sub(Reg, Reg) override;
  void write_sub(Reg, Mem64) override;

  void write_mul(IntReg, i8) override;
  void write_mul(IntReg, IntReg) override;

  void write_div(IntReg, IntReg) override;

  void write_mod(IntReg, IntReg) override;

  void write_bit_and(Reg dst, Reg src) override;

  void write_bit_or(Reg dst, Reg src) override;

  void write_shift_left(UintReg, u8 count) override;
  void write_shift_left(IntReg, u8 count) override;

  void write_shift_right(UintReg, u8 count) override;
  void write_shift_right(IntReg, u8 count) override;

  void write_while_neq(Reg, i8) override;

  void write_if_eq(Reg, i8) override;
  void write_if_else_eq(Reg, i8) override;
};
