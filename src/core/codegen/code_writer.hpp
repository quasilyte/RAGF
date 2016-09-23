#pragma once

#include <core/io/code_buf.hpp>
#include <core/reg.hpp>

class Compiler;

class CodeWriter {
public:
  CodeWriter(CodeBuf);

  void set_compiler(Compiler*);

  int write_block() noexcept;

  Buf get_buf() const noexcept;

  virtual void write_return();
  virtual void write_swap(Reg, Reg);
  virtual void write_neg(Reg);
  virtual void write_assign(Reg dst, Reg src);
  virtual void write_assign(Reg, i32);
  virtual void write_assign(Reg, i64);
  virtual void write_add(Reg, i32);
  virtual void write_add(Reg, i8);
  virtual void write_sub(Reg, i8);
  virtual void write_mul(IntReg, i8);
  virtual void write_div(Reg, Reg);
  virtual void write_mod(Reg, Reg);
  virtual void write_bit_and(Reg, Reg);
  virtual void write_bit_or(Reg, Reg);
  virtual void write_shift_left(Reg, u8);

  virtual void write_while_neq(Reg, i8);
  virtual void write_if_eq(Reg, i8);
  virtual void write_if_else_eq(Reg, i8);

protected:
  Compiler* $compiler;
  CodeBuf $output;
};
