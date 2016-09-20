#pragma once

#include <core/codegen/code_writer.hpp>

namespace x86_64 {
  class CodeWriter;
}

class x86_64::CodeWriter: public ::CodeWriter {
public:
  void write_return() override;
  void write_swap(RegIndex, RegIndex) override;
  void write_neg(RegIndex) override;
  void write_assign(RegIndex, i32) override;
  void write_assign(RegIndex, i64) override;
  void write_add(RegIndex, i32) override;
  void write_add(RegIndex, i8) override;
};
