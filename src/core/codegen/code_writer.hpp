#pragma once

#include <core/io/code_buf.hpp>
#include <core/register.hpp>

class Compiler;

class CodeWriter {
public:
  CodeWriter(CodeBuf);

  void set_compiler(Compiler*);

  int write_block() noexcept;

  Buf get_buf() const noexcept;

  virtual void write_return();
  virtual void write_swap(Register, Register);
  virtual void write_neg(Register);
  virtual void write_assign(Register dst, Register src);
  virtual void write_assign(Register, i32);
  virtual void write_assign(Register, i64);
  virtual void write_add(Register, i32);
  virtual void write_add(Register, i8);
  virtual void write_sub(Register, i8);
  virtual void write_mul(Register, i8);
  virtual void write_div(Register, Register);
  virtual void write_mod(Register, Register);
  virtual void write_bit_and(Register, Register);
  virtual void write_bit_or(Register, Register);

  virtual void write_while_neq(Register, i8);
  virtual void write_if_eq(Register, i8);
  virtual void write_if_else_eq(Register, i8);

protected:
  Compiler* $compiler;
  CodeBuf $output;
};
