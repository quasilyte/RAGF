#include <core/arch/x86_64/ops/ops.hpp>

#include <core/io/code_buf.hpp>
#include <core/arch/x86_64/encode.hpp>
#include <core/codegen/numerics.hpp>

template<>
void Lea::write(CodeBuf* output, Reg dst, Reg a, Imm b) {
  if (fits_i8(b)) {
    output->write(BinaryValue<4>{
      REX_WRB,
      opcode(0x8D),
      mod_reg_rm(Mod::DISP1, dst, a),
      (i8)b
    });
  }
  else if (fits_i32(b)) {
    output->write(BinaryValue<8>{
      REX_WRB,
      opcode(0x8D),
      mod_reg_rm(Mod::DISP4, dst, a),
      (i32)b
    });
  }
  else {
    throw "lea: no support for int64 immediates";
  }
}

template<>
void Lea::write(CodeBuf* output, Reg dst, Reg a, Reg b) {
  static const uint rm = 0b100; // [SIB] addressing

  output->write(BinaryValue<4>{
    REX_WRXB,
    opcode(0x8D),
    mod_reg_rm(Mod::SIB, dst, rm),
    sib(0, b, a)
  });
}
