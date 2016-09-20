#pragma once

#include <core/io/code_buf.hpp>
#include <core/reg_index.hpp>

class CodeWriter {
public:
  CodeWriter();

  Buf get_buf() const noexcept;

  virtual void write_return();
  virtual void write_assign(RegIndex, i32);
  virtual void write_assign(RegIndex, i64);
  virtual void write_add(RegIndex, i32);

protected:
  CodeBuf $output;
};
