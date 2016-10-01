#include <core/arch/x86_64/ops/ops.hpp>

#include <core/io/code_buf.hpp>
#include <core/arch/x86_64/encode.hpp>
#include <core/codegen/numerics.hpp>

template<> int Cmp::size(Reg, i64 imm) {
  switch (min_width(imm)) {
  case Size::BYTE: return 4;
  case Size::WORD:
  case Size::DWORD: return 7;
  default: return -1;
  }
}

template<>
void Cmp::write(CodeBuf* output, Reg a, i64 b) {
  if (fits_i8(b)) {
    output->write(BinaryValue<4>{
      REX_WB,
      opcode(0x83),
      mod_reg_rm(Mod::REG, 7, a),
      (i8)b
    });
  }
  else if (fits_i32(b)) {
    output->write(BinaryValue<8>{
      REX_WB,
      opcode(0x81),
      mod_reg_rm(Mod::REG, 7, a),
      (i32)b
    });
  }
  else {
    throw "cmp: only {8,32} bit immediates are implemented";
  }
}
