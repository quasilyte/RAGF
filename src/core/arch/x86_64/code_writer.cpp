#include <core/arch/x86_64/code_writer.hpp>

#include <core/arch/x86_64/constants.hpp>
#include <core/arch/x86_64/encode.hpp>

#define CodeWriter x86_64::CodeWriter

void CodeWriter::write_return() {
  $output.write_byte(0xC3);
}

void CodeWriter::write_swap(RegIndex a, RegIndex b) {
  $output.write(BinaryValue<4>{
    REX_WRB,
    opcode(0x87),
    mod_reg_rm(Mod::REG, a, b)
  });
}

void CodeWriter::write_neg(RegIndex r) {
  $output.write(BinaryValue<8>{
    REX_WB,
    opcode(0xF7),
    mod_reg_rm(Mod::REG, 3, r)
  });
}

void CodeWriter::write_assign(RegIndex idx, i32 val) {
  $output.write(BinaryValue<8>{
    REX_WB,
    opcode(0xC7),
    mod_reg_rm(Mod::REG, 0, idx),
    val
  });
}

void CodeWriter::write_assign(RegIndex idx, i64 val) {
  $output.write(BinaryValue<16>{
    REX_WB, opcode(0xB8, idx), val
  });
}

void CodeWriter::write_add(RegIndex idx, i32 val) {
  $output.write(BinaryValue<8>{
    REX_WB,
    opcode(0x81),
    mod_reg_rm(Mod::REG, 0, idx),
    val
  });
}

void CodeWriter::write_add(RegIndex idx, i8 val) {
  $output.write(BinaryValue<8>{
    REX_WB,
    opcode(0x83),
    mod_reg_rm(Mod::REG, 0, idx),
    val
  });
}