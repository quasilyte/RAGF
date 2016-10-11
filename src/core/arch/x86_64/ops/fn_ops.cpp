#include <core/arch/x86_64/ops/ops.hpp>

#include <core/io/code_buf.hpp>
#include <core/arch/x86_64/encode.hpp>

int Ret::size() { return 1; }
void Ret::write(CodeBuf* output) {
  output->write_byte(0xC3);
}

template<>
void Call::write(CodeBuf* output, Reg fn_ptr) {
  *output << BinaryValue<4>{
    REX_B,
    opcode(0xFF),
    mod_reg_rm(Mod::REG, 2, fn_ptr)
  };
}
