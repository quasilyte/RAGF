#include <core/arch/x86_64/ops/ops.hpp>

#include <core/io/code_buf.hpp>
#include <core/arch/x86_64/encode.hpp>
#include <core/arch/x86_64/gpr_tags.hpp>
#include <core/codegen/numerics.hpp>

template<>
void Mov::write(CodeBuf* output, Gpr dst, Reg src) {
  output->write(BinaryValue<4>{
    REX_WR,
    opcode(0x89),
    mod_reg_rm(Mod::REG, src, dst)
  });
}

template<>
void Mov::write(CodeBuf* output, Reg dst, Gpr src) {
  output->write(BinaryValue<4>{
    REX_WB,
    opcode(0x89),
    mod_reg_rm(Mod::REG, src, dst)
  });
}

template<>
void Mov::write(CodeBuf* output, Reg dst, Reg src) {
  output->write(BinaryValue<4>{
    REX_WRB,
    opcode(0x89),
    mod_reg_rm(Mod::REG, src, dst)
  });
}

template<>
void Mov::write(CodeBuf* output, Reg dst, i64 src) {
  if (fits_i32(src)) {
    output->write(BinaryValue<8>{
      REX_WB,
      opcode(0xC7),
      mod_reg_rm(Mod::REG, 0, dst),
      src
    });
  } else {
    output->write(BinaryValue<16>{
      REX_WB,
      opcode(0xB8, dst),
      src
    });
  }
}

template<>
void Mov::write(CodeBuf *output, Reg dst, Mem64 src, i8 disp) {
  if (disp == 0) {
    output->write(BinaryValue<4>{
      REX_WRB,
      opcode(0x8B),
      mod_reg_rm(Mod::SIB, dst, src)
    });
  } else {
    output->write(BinaryValue<4>{
      REX_WRB,
      opcode(0x8B),
      mod_reg_rm(Mod::DISP1, dst, src),
      disp
    });
  }
}

template<>
void Mov::write(CodeBuf *output, Mem64 dst, Reg src, i8 disp) {
  if (disp == 0) {
    output->write(BinaryValue<4>{
      REX_WRB,
      opcode(0x89),
      mod_reg_rm(Mod::SIB, src, dst)
    });
  } else {
    output->write(BinaryValue<4>{
      REX_WRB,
      opcode(0x89),
      mod_reg_rm(Mod::DISP1, src, dst),
      disp
    });
  }
}
