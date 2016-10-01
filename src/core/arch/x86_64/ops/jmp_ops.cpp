#include <core/arch/x86_64/ops/ops.hpp>

#include <core/io/code_buf.hpp>
#include <core/arch/x86_64/encode.hpp>

template<> int Jne::size(i32) { return 6; }
template<>
void Jne::write(CodeBuf* output, i32 offset) {
  output->write(BinaryValue<8>{
    opcode(0x0F, 0x85),
    offset
  });
}

template<> int Jmp::size(i32) { return 5; }
template<>
void Jmp::write(CodeBuf* output, i32 offset) {
  output->write(BinaryValue<8>{
    opcode(0xE9),
    offset
  });
}
