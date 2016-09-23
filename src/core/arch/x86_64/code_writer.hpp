#pragma once

#include <core/codegen/code_writer.hpp>

namespace x86_64 {
  class CodeWriter;
}

class x86_64::CodeWriter: public ::CodeWriter {
public:
  using ::CodeWriter::CodeWriter;

  void write_return() override;
  void write_swap(Reg, Reg) override;
  void write_neg(Reg) override;
  void write_assign(Reg dst, Reg src) override;
  void write_assign(Reg, i32) override;
  void write_assign(Reg, i64) override;
  void write_add(Reg, i32) override;
  void write_add(Reg, i8) override;
  void write_sub(Reg, i8) override;
  void write_mul(Reg, i8) override;
  void write_div(Reg, Reg) override;
  void write_mod(Reg, Reg) override;
  void write_bit_and(Reg, Reg) override;
  void write_bit_or(Reg, Reg) override;
  void write_shift_left(Reg, u8) override;
  void write_while_neq(Reg, i8) override;
  void write_if_eq(Reg, i8) override;
  void write_if_else_eq(Reg, i8) override;
};
