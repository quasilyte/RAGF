#include <core/arch/x86_64/ops/ops.hpp>

#include <core/io/code_buf.hpp>
#include <core/arch/x86_64/encode.hpp>
#include <core/codegen/numerics.hpp>

template<>
void Mov::write(CodeBuf* output, Gpr dst, Reg src) {
  *output << BinaryValue<4>{
    REX_WR,
    opcode(0x89),
    mod_reg_rm(Mod::REG, src, dst)
  };
}

template<>
void Mov::write(CodeBuf* output, Gpr dst, Mem src) {
  if (src.byte_count == 8) {
    if (src.disp() == 0) {
      *output << BinaryValue<4>{
        REX_WB,
        opcode(0x8B),
        mod_reg_rm(Mod::SIB, dst, src.ptr)
      };
    }
    else if (fits_i8(src.disp())) {
      *output << BinaryValue<4>{
        REX_WB,
        opcode(0x8B),
        mod_reg_rm(Mod::DISP1, dst, src.ptr),
        (i8)src.disp()
      };
    }
    else {
      throw "mov: invalid displacement";
    }
  }
  else {
    throw "mov: invalid memory cell size";
  }
}

template<>
void Mov::write(CodeBuf* output, Mem dst, Gpr src) {
  if (dst.byte_count == 8) {
    if (dst.disp() == 0) {
      *output << BinaryValue<4>{
        REX_WB,
        opcode(0x89),
        mod_reg_rm(Mod::SIB, src, dst.ptr)
      };
    }
    else if (fits_i8(dst.disp())) {
      *output << BinaryValue<4>{
        REX_WB,
        opcode(0x89),
        mod_reg_rm(Mod::DISP1, src, dst.ptr),
        (i8)dst.disp()
      };
    }
    else {
      throw "mov: invalid displacement";
    }
  }
  else {
    throw "mov: invalid memory cell size";
  }
}

template<>
void Mov::write(CodeBuf* output, Reg dst, Gpr src) {
  *output << BinaryValue<4>{
    REX_WB,
    opcode(0x89),
    mod_reg_rm(Mod::REG, src, dst)
  };
}

template<>
void Mov::write(CodeBuf* output, Reg dst, Reg src) {
  *output << BinaryValue<4>{
    REX_WRB,
    opcode(0x89),
    mod_reg_rm(Mod::REG, src, dst)
  };
}

template<>
void Mov::write(CodeBuf* output, Reg dst, i64 src) {
  if (fits_i32(src)) {
    *output << BinaryValue<8>{
      REX_WB,
      opcode(0xC7),
      mod_reg_rm(Mod::REG, 0, dst),
      src
    };
  } else {
    *output << BinaryValue<16>{
      REX_WB,
      opcode(0xB8, dst),
      src
    };
  }
}

template<>
void Mov::write(CodeBuf* output, Mem dst, Reg src) {
  if (dst.byte_count == 8) {
    if (dst.index == 0) {
      *output << BinaryValue<4>{
        REX_WRB,
        opcode(0x89),
        mod_reg_rm(Mod::SIB, src, dst.ptr)
      };
    }
    else if (fits_i8(dst.disp())) {
      *output << BinaryValue<4>{
        REX_WRB,
        opcode(0x89),
        mod_reg_rm(Mod::DISP1, src, dst.ptr),
        (i8)dst.disp()
      };
    }
    else {
      throw "mov: invalid displacement";
    }
  }
  else {
    throw "mov: invalid memory cell size";
  }
}

template<>
void Mov::write(CodeBuf* output, Reg dst, Mem src) {
  if (src.byte_count == 8) {
    if (src.index == 0) {
      *output << BinaryValue<4>{
        REX_WRB,
        opcode(0x8B),
        mod_reg_rm(Mod::SIB, dst, src.ptr)
      };
    }
    else if (fits_i8(src.disp())) {
      *output << BinaryValue<4>{
        REX_WRB,
        opcode(0x8B),
        mod_reg_rm(Mod::DISP1, dst, src.ptr),
        (i8)src.disp()
      };
    }
    else {
      throw "mov: invalid displacement";
    }
  }
  else {
    throw "mov: invalid memory cell size";
  }
}
