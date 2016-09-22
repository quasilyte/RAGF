#include <core/arch/x86_64/code_writer.hpp>

#include <core/arch/x86_64/ops.hpp>
#include <core/compile/compiler.hpp>

#define CodeWriter x86_64::CodeWriter

void CodeWriter::write_return() {
  Ret::write(&$output);
}

void CodeWriter::write_swap(RegIndex a, RegIndex b) {
  Xchg::write(&$output, a, b);
}

void CodeWriter::write_neg(RegIndex r) {
  Neg::write(&$output, r);
}

void CodeWriter::write_assign(RegIndex dst, RegIndex src) {
  Mov::write(&$output, dst, src);
}

void CodeWriter::write_assign(RegIndex dst, i32 src) {
  Mov::write(&$output, dst, src);
}

void CodeWriter::write_assign(RegIndex dst, i64 src) {
  Mov::write(&$output, dst, src);
}

void CodeWriter::write_add(RegIndex dst, i32 src) {
  Add::write(&$output, dst, src);
}

void CodeWriter::write_add(RegIndex dst, i8 src) {
  Add::write(&$output, dst, src);
}

void CodeWriter::write_sub(RegIndex dst, i8 src) {
  Sub::write(&$output, dst, src);
}

void CodeWriter::write_while_neq(RegIndex a, i8 b) {
  auto jmp_block = $output.preserve(Jmp::size(i32{}));
  int body_size = write_block();
  Jmp::write(jmp_block, body_size);

  Cmp::write(&$output, a, b);
  Jne::write(&$output, -(body_size + Jne::size(i32{}) + Cmp::size(a, b)));
}

void CodeWriter::write_if_eq(RegIndex a, i8 b) {
  Cmp::write(&$output, a, b);

  auto jne_block = $output.preserve(Jne::size(i32{}));
  int on_true_size = write_block();
  Jne::write(jne_block, on_true_size);
}

void CodeWriter::write_if_else_eq(RegIndex a, i8 b) {
  Cmp::write(&$output, a, b);

  auto jne_block = $output.preserve(Jne::size(i32{}));
  int on_true_size = write_block();
  Jne::write(jne_block, on_true_size + Jmp::size(i32{}));

  auto jmp_block = $output.preserve(Jmp::size(i32{}));
  int on_false_size = write_block();
  Jmp::write(jmp_block, on_false_size);
}
