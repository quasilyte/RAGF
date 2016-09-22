#include <core/arch/x86_64/ops.hpp>

#include <core/io/code_buf.hpp>
#include <core/arch/x86_64/encode.hpp>

int Ret::size() { return 1; }
void Ret::write(CodeBuf* output) {
  output->write_byte(0xC3);
}

template<>
void Mov::write(CodeBuf* output, RegIndex dst, RegIndex src) {
  output->write(BinaryValue<8>{
    REX_WRB,
    opcode(0x89),
    mod_reg_rm(Mod::REG, src, dst)
  });
}
template<>
void Mov::write(CodeBuf* output, RegIndex dst, i32 src) {
  output->write(BinaryValue<8>{
    REX_WB,
    opcode(0xC7),
    mod_reg_rm(Mod::REG, 0, dst),
    src
  });
}
template<>
void Mov::write(CodeBuf *output, RegIndex dst, i64 src) {
  output->write(BinaryValue<16>{
    REX_WB,
    opcode(0xB8, dst),
    src
  });
}

template<>
void Sub::write(CodeBuf* output, RegIndex dst, i8 src) {
  output->write(BinaryValue<8>{
    REX_WB,
    opcode(0x83),
    mod_reg_rm(Mod::REG, 5, dst),
    src
  });
}

template<>
void Add::write(CodeBuf* output, RegIndex dst, i8 src) {
  output->write(BinaryValue<8>{
    REX_WB,
    opcode(0x83),
    mod_reg_rm(Mod::REG, 0, dst),
    src
  });
}
template<>
void Add::write(CodeBuf* output, RegIndex dst, i32 src) {
  output->write(BinaryValue<8>{
    REX_WB,
    opcode(0x81),
    mod_reg_rm(Mod::REG, 0, dst),
    src
  });
}

template<>
void Neg::write(CodeBuf* output, RegIndex r) {
  output->write(BinaryValue<8>{
    REX_WB,
    opcode(0xF7),
    mod_reg_rm(Mod::REG, 3, r)
  });
}

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

template<>
void Xchg::write(CodeBuf* output, RegIndex a, RegIndex b) {
  output->write(BinaryValue<4>{
    REX_WRB,
    opcode(0x87),
    mod_reg_rm(Mod::REG, a, b)
  });
}

template<> int Cmp::size(RegIndex, i8) { return 4; }
template<>
void Cmp::write(CodeBuf* output, RegIndex a, i8 b) {
  output->write(BinaryValue<4>{
    REX_WB,
    opcode(0x83),
    mod_reg_rm(Mod::REG, 7, a),
    b
  });
}
