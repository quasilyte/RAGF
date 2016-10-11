#include <core/arch/x86_64/ops/ops.hpp>

#include <core/io/code_buf.hpp>
#include <core/arch/x86_64/encode.hpp>

template<>
void Shl::write(CodeBuf* output, Reg r, u8 count) {
  if (count == 1) {
    *output << BinaryValue<8>{
      REX_WB,
      opcode(0xD1),
      mod_reg_rm(Mod::REG, 4, r),
    };
  } else {
    *output << BinaryValue<8>{
      REX_WB,
      opcode(0xC1),
      mod_reg_rm(Mod::REG, 4, r),
      count
    };
  }
}

template<>
void Shr::write(CodeBuf* output, UintReg r, u8 count) {
  if (count == 1) {
    *output << BinaryValue<4>{
      REX_WB,
      opcode(0xD1),
      mod_reg_rm(Mod::REG, 5, r)
    };
  } else {
    *output << BinaryValue<4>{
      REX_WB,
      opcode(0xC1),
      mod_reg_rm(Mod::REG, 5, r),
      count
    };
  }
}

template<>
void Sar::write(CodeBuf* output, IntReg r, u8 count) {
  if (count == 1) {
    *output << BinaryValue<4>{
      REX_WB,
      opcode(0xD1),
      mod_reg_rm(Mod::REG, 7, r)
    };
  } else {
    *output << BinaryValue<4>{
      REX_WB,
      opcode(0xC1),
      mod_reg_rm(Mod::REG, 7, r),
      count
    };
  }
}
