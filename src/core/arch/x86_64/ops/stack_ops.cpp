#include <core/arch/x86_64/ops/ops.hpp>

#include <core/io/code_buf.hpp>
#include <core/arch/x86_64/encode.hpp>

template<>
void Push::write(CodeBuf* output, Reg r) {
  output->write(BinaryValue<2>{
    REX_B,
    opcode(0x50, r)
  });
}

template<>
void Pop::write(CodeBuf* output, Reg r) {
  output->write(BinaryValue<2>{
    REX_B,
    opcode(0x58, r)
  });
}
