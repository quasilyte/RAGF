#include <core/arch/x86_64/ops/ops.hpp>

#include <core/io/code_buf.hpp>
#include <core/arch/x86_64/encode.hpp>
#include <core/arch/x86_64/gpr_tags.hpp>
#include <core/codegen/numerics.hpp>

int Nop::size() { return 1; }
void Nop::write(CodeBuf* output) {
  output->write_byte(0x90);
}

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
void Imul::write(CodeBuf* output, IntReg dst, IntReg a, i64 src) {
  if (fits_i8(src)) {
    output->write(BinaryValue<4>{
      REX_WRB,
      opcode(0x6B),
      mod_reg_rm(Mod::REG, dst, a),
      (i8)src
    });
  }
  else {
    throw "imul: only 8 bit immediates are implemented";
  }
}
template<>
void Imul::write(CodeBuf* output, IntReg dst, IntReg src) {
  output->write(BinaryValue<4>{
    REX_WRB,
    opcode(0x0F, 0xAF),
    mod_reg_rm(Mod::REG, dst, src)
  });
}

template<>
void Idiv::write(CodeBuf* output, IntReg divider) {
  output->write(BinaryValue<8>{
    REX_WB,
    opcode(0xF7),
    mod_reg_rm(Mod::REG, 7, divider)
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
void Xchg::write(CodeBuf* output, Reg a, Reg b) {
  output->write(BinaryValue<4>{
    REX_WRB,
    opcode(0x87),
    mod_reg_rm(Mod::REG, a, b)
  });
}

template<> int Cmp::size(Reg, i64 imm) {
  switch (min_width(imm)) {
  case Size::BYTE: return 4;
  case Size::WORD:
  case Size::DWORD: return 7;
  default: return -1;
  }
}

template<>
void Cmp::write(CodeBuf* output, Reg a, i64 b) {
  if (fits_i8(b)) {
    output->write(BinaryValue<4>{
      REX_WB,
      opcode(0x83),
      mod_reg_rm(Mod::REG, 7, a),
      (i8)b
    });
  }
  else if (fits_i32(b)) {
    output->write(BinaryValue<8>{
      REX_WB,
      opcode(0x81),
      mod_reg_rm(Mod::REG, 7, a),
      (i32)b
    });
  }
  else {
    throw "cmp: only {8,32} bit immediates are implemented";
  }
}

template<>
void Shl::write(CodeBuf* output, Reg r, u8 count) {
  if (count == 1) {
    output->write(BinaryValue<8>{
      REX_WB,
      opcode(0xD1),
      mod_reg_rm(Mod::REG, 4, r),
    });
  } else {
    output->write(BinaryValue<8>{
      REX_WB,
      opcode(0xC1),
      mod_reg_rm(Mod::REG, 4, r),
      count
    });
  }
}

template<>
void Shr::write(CodeBuf* output, UintReg r, u8 count) {
  if (count == 1) {
    output->write(BinaryValue<4>{
      REX_WB,
      opcode(0xD1),
      mod_reg_rm(Mod::REG, 5, r)
    });
  } else {
    output->write(BinaryValue<4>{
      REX_WB,
      opcode(0xC1),
      mod_reg_rm(Mod::REG, 5, r),
      count
    });
  }
}

template<>
void Sar::write(CodeBuf* output, IntReg r, u8 count) {
  if (count == 1) {
    output->write(BinaryValue<4>{
      REX_WB,
      opcode(0xD1),
      mod_reg_rm(Mod::REG, 7, r)
    });
  } else {
    output->write(BinaryValue<4>{
      REX_WB,
      opcode(0xC1),
      mod_reg_rm(Mod::REG, 7, r),
      count
    });
  }
}

template<>
void Call::write(CodeBuf* output, Reg fn_ptr) {
  output->write(BinaryValue<4>{
    REX_B,
    opcode(0xFF),
    mod_reg_rm(Mod::REG, 2, fn_ptr)
  });
}

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
