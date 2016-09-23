#include <core/arch/x86_64/ops.hpp>

#include <core/io/code_buf.hpp>
#include <core/arch/x86_64/encode.hpp>
#include <core/arch/x86_64/gpr_tags.hpp>

int Ret::size() { return 1; }
void Ret::write(CodeBuf* output) {
  output->write_byte(0xC3);
}

int Cqo::size() { return 2; }
void Cqo::write(CodeBuf* output) {
  output->write_byte(REX_W);
  output->write_byte(0x99);
}

template<>
void Mov::write(CodeBuf* output, Gpr dst, Register src) {
  output->write(BinaryValue<4>{
    REX_WR,
    opcode(0x89),
    mod_reg_rm(Mod::REG, src, dst)
  });
}
template<>
void Mov::write(CodeBuf* output, Register dst, Gpr src) {
  output->write(BinaryValue<4>{
    REX_WB,
    opcode(0x89),
    mod_reg_rm(Mod::REG, src, dst)
  });
}
template<>
void Mov::write(CodeBuf* output, Register dst, Register src) {
  output->write(BinaryValue<4>{
    REX_WRB,
    opcode(0x89),
    mod_reg_rm(Mod::REG, src, dst)
  });
}
template<>
void Mov::write(CodeBuf* output, Register dst, i32 src) {
  output->write(BinaryValue<8>{
    REX_WB,
    opcode(0xC7),
    mod_reg_rm(Mod::REG, 0, dst),
    src
  });
}
template<>
void Mov::write(CodeBuf *output, Register dst, i64 src) {
  output->write(BinaryValue<16>{
    REX_WB,
    opcode(0xB8, dst),
    src
  });
}

template<>
void Sub::write(CodeBuf* output, Register dst, i8 src) {
  output->write(BinaryValue<8>{
    REX_WB,
    opcode(0x83),
    mod_reg_rm(Mod::REG, 5, dst),
    src
  });
}

template<>
void And::write(CodeBuf* output, Register dst, Register src) {
  output->write(BinaryValue<4>{
    REX_WRB,
    opcode(0x21),
    mod_reg_rm(Mod::REG, src, dst)
  });
}

template<>
void Or::write(CodeBuf* output, Register dst, Register src) {
  output->write(BinaryValue<4>{
    REX_WRB,
    opcode(0x09),
    mod_reg_rm(Mod::REG, src, dst)
  });
}

template<>
void Imul::write(CodeBuf* output, Register dst, Register a, i8 src) {
  output->write(BinaryValue<4>{
    REX_WRB,
    opcode(0x6B),
    mod_reg_rm(Mod::REG, dst, a),
    src
  });
}


template<>
void Idiv::write(CodeBuf* output, Register divider) {
  output->write(BinaryValue<8>{
    REX_WB,
    opcode(0xF7),
    mod_reg_rm(Mod::REG, 7, divider)
  });
}

template<>
void Add::write(CodeBuf* output, Register dst, i8 src) {
  output->write(BinaryValue<8>{
    REX_WB,
    opcode(0x83),
    mod_reg_rm(Mod::REG, 0, dst),
    src
  });
}
template<>
void Add::write(CodeBuf* output, Register dst, i32 src) {
  output->write(BinaryValue<8>{
    REX_WB,
    opcode(0x81),
    mod_reg_rm(Mod::REG, 0, dst),
    src
  });
}

template<>
void Neg::write(CodeBuf* output, Register r) {
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
void Xchg::write(CodeBuf* output, Register a, Register b) {
  output->write(BinaryValue<4>{
    REX_WRB,
    opcode(0x87),
    mod_reg_rm(Mod::REG, a, b)
  });
}

template<> int Cmp::size(Register, i8) { return 4; }
template<>
void Cmp::write(CodeBuf* output, Register a, i8 b) {
  output->write(BinaryValue<4>{
    REX_WB,
    opcode(0x83),
    mod_reg_rm(Mod::REG, 7, a),
    b
  });
}
