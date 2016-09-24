#pragma once

#include <core/io/code_buf.hpp>
#include <core/reg.hpp>
#include <core/special_tags.hpp>

class Compiler;

class CodeWriter {
public:
  CodeWriter(CodeBuf);

  void set_compiler(Compiler*);

  int write_block() noexcept;

  Buf get_buf() const noexcept;

  virtual void write_return();
  virtual void write_neg(Reg);
  virtual void write_swap(Reg, Reg);

  virtual void write_assign(Reg, i32);
  virtual void write_assign(Reg, i64);
  virtual void write_assign(Reg dst, Reg src);
  virtual void write_assign(Reg, Mem64, i8);
  virtual void write_assign(Reg, DataReg);

  virtual void write_add(Reg, i8);
  virtual void write_add(Reg, i32);
  virtual void write_add(Reg, Reg);
  virtual void write_add(Reg, Mem64);

  virtual void write_sub(Reg, i8);
  virtual void write_sub(Reg, i32);
  virtual void write_sub(Reg, Reg);
  virtual void write_sub(Reg, Mem64);

  virtual void write_mul(IntReg, i8);

  virtual void write_div(IntReg, IntReg);

  virtual void write_mod(IntReg, IntReg);

  virtual void write_bit_and(Reg dst, Reg src);

  virtual void write_bit_or(Reg dst, Reg src);

  virtual void write_shift_left(UintReg, u8 count);
  virtual void write_shift_left(IntReg, u8 count);

  virtual void write_shift_right(UintReg, u8 count);
  virtual void write_shift_right(IntReg, u8 count);

  virtual void write_while_neq(Reg, i8);

  virtual void write_if_eq(Reg, i8);
  virtual void write_if_else_eq(Reg, i8);

protected:
  Compiler* $compiler;
  CodeBuf $output;
};
