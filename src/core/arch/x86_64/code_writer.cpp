#include <core/arch/x86_64/code_writer.hpp>

#include <core/arch/x86_64/constants.hpp>
#include <core/arch/x86_64/encode.hpp>

int write_jne(CodeBuf* output, i32 offset) {
  return output->write(BinaryValue<8>{
    opcode(0x0F, 0x85),
    offset
  });
}

int write_jmp(CodeBuf* output,  i32 offset) {
  return output->write(BinaryValue<8>{
    opcode(0xE9),
    offset
  });
}

int write_cmp(CodeBuf* output, RegIndex a, i8 b) {
  return output->write(BinaryValue<4>{
    REX_WB,
    opcode(0x83),
    mod_reg_rm(Mod::REG, 7, a),
    b
  });
}

#define CodeWriter x86_64::CodeWriter

void CodeWriter::write_return() {
  $output->write_byte(0xC3);
}

void CodeWriter::write_swap(RegIndex a, RegIndex b) {
  $output->write(BinaryValue<4>{
    REX_WRB,
    opcode(0x87),
    mod_reg_rm(Mod::REG, a, b)
  });
}

void CodeWriter::write_neg(RegIndex r) {
  $output->write(BinaryValue<8>{
    REX_WB,
    opcode(0xF7),
    mod_reg_rm(Mod::REG, 3, r)
  });
}

void CodeWriter::write_assign(RegIndex idx, i32 val) {
  $output->write(BinaryValue<8>{
    REX_WB,
    opcode(0xC7),
    mod_reg_rm(Mod::REG, 0, idx),
    val
  });
}

void CodeWriter::write_assign(RegIndex idx, i64 val) {
  $output->write(BinaryValue<16>{
    REX_WB, opcode(0xB8, idx), val
  });
}

void CodeWriter::write_add(RegIndex idx, i32 val) {
  $output->write(BinaryValue<8>{
    REX_WB,
    opcode(0x81),
    mod_reg_rm(Mod::REG, 0, idx),
    val
  });
}

void CodeWriter::write_add(RegIndex idx, i8 val) {
  $output->write(BinaryValue<8>{
    REX_WB,
    opcode(0x83),
    mod_reg_rm(Mod::REG, 0, idx),
    val
  });
}

void CodeWriter::write_sub(RegIndex idx, i8 val) {
  $output->write(BinaryValue<8>{
    REX_WB,
    opcode(0x83),
    mod_reg_rm(Mod::REG, 5, idx),
    val
  });
}

void CodeWriter::write_loop(i32 offset) {
  write_jmp($output, offset);
}

void CodeWriter::write_while_neq(i32 offset, RegIndex a, i8 b) {
  const int jmp_size = 6;

  int cmp_size = write_cmp($output, a, b);
  int encoded_size = cmp_size + jmp_size;
  write_jne($output, -(offset + encoded_size));
}
