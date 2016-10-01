#include <core/arch/x86_64/ops/ops.hpp>

#include <core/io/code_buf.hpp>
#include <core/arch/x86_64/encode.hpp>
#include <core/codegen/numerics.hpp>
#include <core/mem.hpp>

template<>
void Add::write(CodeBuf* output, Reg dst, i64 src) {
  if (fits_i8(src)) {
    output->write(BinaryValue<8>{
      REX_WB,
      opcode(0x83),
      mod_reg_rm(Mod::REG, 0, dst),
      (i8)src
    });
  }
  else if (fits_i32(src)) {
    output->write(BinaryValue<8>{
      REX_WB,
      opcode(0x83),
      mod_reg_rm(Mod::REG, 0, dst),
      (i32)src
    });
  }
  else {
    throw "add: no support for int64 immediates";
  }
}

template<>
void Add::write(CodeBuf *output, Reg dst, Reg src) {
  output->write(BinaryValue<4>{
    REX_WRB,
    opcode(0x01),
    mod_reg_rm(Mod::REG, src, dst)
  });
}

template<>
void Add::write(CodeBuf* output, Reg dst, Mem src) {
  if (src.byte_count == 8) {
    if (src.disp() == 0) {
      output->write(BinaryValue<4>{
        REX_WRB,
        opcode(0x03),
        mod_reg_rm(Mod::SIB, dst, src.ptr)
      });
    }
    else {
      throw "add: invalid displacement";
    }
  }
  else {
    throw "add: invalid memory cell size";
  }
}
