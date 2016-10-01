#include <core/arch/x86_64/ops/ops.hpp>

#include <core/io/code_buf.hpp>
#include <core/arch/x86_64/encode.hpp>

int Nop::size() { return 1; }
void Nop::write(CodeBuf* output) {
  output->write_byte(0x90);
}

int Cqo::size() { return 2; }
void Cqo::write(CodeBuf* output) {
  output->write_byte(REX_W);
  output->write_byte(0x99);
}

template<>
void Xchg::write(CodeBuf* output, Reg a, Reg b) {
  output->write(BinaryValue<4>{
    REX_WRB,
    opcode(0x87),
    mod_reg_rm(Mod::REG, a, b)
  });
}
