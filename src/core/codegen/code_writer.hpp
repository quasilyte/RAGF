#pragma once

#include <core/io/code_buf.hpp>
#include <core/reg.hpp>
#include <core/special_tags.hpp>
#include <core/mem.hpp>

class Compiler;

typedef i64 Imm;

class CodeWriter {
public:
  CodeWriter(CodeBuf);

  void set_compiler(Compiler*);

  int write_block() noexcept;

  Buf get_buf() const noexcept;

  virtual void write_return();
  virtual void write_return(Reg);

  virtual void write_push(const Reg*, int count);
  virtual void write_pop(const Reg*, int count);

  virtual void write_neg(Reg);
  virtual void write_swap(Reg, Reg);

  virtual void write_assign(Reg, Imm);
  virtual void write_assign(Reg dst, Reg src);
  virtual void write_assign(Reg, Mem);
  virtual void write_assign(Mem, Reg);
  virtual void write_assign(Reg, DataReg);

  virtual void write_add(Reg, Imm);
  virtual void write_add(Reg, Reg);
  virtual void write_add(Reg, Mem);

  virtual void write_sub(Reg, Imm);
  virtual void write_sub(Reg, Reg);
  virtual void write_sub(Reg, Mem);

  virtual void write_mul(IntReg, Imm);
  virtual void write_mul(IntReg, IntReg);

  virtual void write_div(IntReg, IntReg);

  virtual void write_mod(IntReg, IntReg);

  virtual void write_bit_and(Reg dst, Reg src);

  virtual void write_bit_or(Reg dst, Reg src);

  virtual void write_shift_left(UintReg, u8 count);
  virtual void write_shift_left(IntReg, u8 count);

  virtual void write_shift_right(UintReg, u8 count);
  virtual void write_shift_right(IntReg, u8 count);

  virtual void write_while_neq(Reg, Imm);

  virtual void write_if_eq(Reg, Imm);
  virtual void write_if_else_eq(Reg, Imm);

protected:
  Compiler* $compiler;
  CodeBuf $output;
};
