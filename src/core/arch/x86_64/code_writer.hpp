#pragma once

#include <core/codegen/code_writer.hpp>

namespace x86_64 {
  class CodeWriter;
}

class x86_64::CodeWriter: public ::CodeWriter {
public:
  using ::CodeWriter::CodeWriter;

  void write_return() override;
  void write_swap(Register, Register) override;
  void write_neg(Register) override;
  void write_assign(Register dst, Register src) override;
  void write_assign(Register, i32) override;
  void write_assign(Register, i64) override;
  void write_add(Register, i32) override;
  void write_add(Register, i8) override;
  void write_sub(Register, i8) override;
  void write_mul(Register, i8) override;
  void write_div(Register, Register) override;
  void write_mod(Register, Register) override;
  void write_bit_and(Register, Register) override;
  void write_bit_or(Register, Register) override;
  void write_while_neq(Register, i8) override;
  void write_if_eq(Register, i8) override;
  void write_if_else_eq(Register, i8) override;
};
