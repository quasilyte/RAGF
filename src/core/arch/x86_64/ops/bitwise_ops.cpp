#include <core/arch/x86_64/ops/ops.hpp>

#include <core/io/code_buf.hpp>
#include <core/arch/x86_64/encode.hpp>

template<>
void And::write(CodeBuf* output, Reg dst, Reg src) {
  output->write(BinaryValue<4>{
    REX_WRB,
    opcode(0x21),
    mod_reg_rm(Mod::REG, src, dst)
  });
}

template<>
void Xor::write(CodeBuf* output, Reg dst, Reg src) {
  output->write(BinaryValue<4>{
    REX_WRB,
    opcode(0x31),
    mod_reg_rm(Mod::REG, src, dst)
  });
}

template<>
void Or::write(CodeBuf* output, Reg dst, Reg src) {
  output->write(BinaryValue<4>{
    REX_WRB,
    opcode(0x09),
    mod_reg_rm(Mod::REG, src, dst)
  });
}

template<>
void Neg::write(CodeBuf* output, Reg r) {
  output->write(BinaryValue<8>{
    REX_WB,
    opcode(0xF7),
    mod_reg_rm(Mod::REG, 3, r)
  });
}
