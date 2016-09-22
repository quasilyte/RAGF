#pragma once

#include <core/io/code_buf.hpp>
#include <core/reg_index.hpp>

class Compiler;

class CodeWriter {
public:
  CodeWriter(CodeBuf);

  void set_compiler(Compiler*);

  Buf get_buf() const noexcept;

  int write_block() noexcept;

  virtual void write_return();
  virtual void write_swap(RegIndex, RegIndex);
  virtual void write_neg(RegIndex);
  virtual void write_assign(RegIndex dst, RegIndex src);
  virtual void write_assign(RegIndex, i32);
  virtual void write_assign(RegIndex, i64);
  virtual void write_add(RegIndex, i32);
  virtual void write_add(RegIndex, i8);
  virtual void write_sub(RegIndex, i8);

  virtual void write_while_neq(RegIndex, i8);

//  virtual void write_loop(i32 offset);
//  virtual void write_while_neq(i32 offset, RegIndex, i8);

protected:
  Compiler* $compiler;
  CodeBuf $output;
};
