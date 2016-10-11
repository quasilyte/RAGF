#include <core/arch/x86_64/ops/ops.hpp>

#include <core/io/code_buf.hpp>
#include <core/arch/x86_64/encode.hpp>
#include <core/codegen/numerics.hpp>

template<>
void Imul::write(CodeBuf* output, IntReg dst, IntReg a, i64 src) {
  if (fits_i8(src)) {
    *output << BinaryValue<4>{
      REX_WRB,
      opcode(0x6B),
      mod_reg_rm(Mod::REG, dst, a),
      (i8)src
    };
  }
  else {
    throw "imul: only 8 bit immediates are implemented";
  }
}

template<>
void Imul::write(CodeBuf* output, IntReg dst, IntReg src) {
  *output << BinaryValue<4>{
    REX_WRB,
    opcode(0x0F, 0xAF),
    mod_reg_rm(Mod::REG, dst, src)
  };
}
