#include <core/arch/x86_64/code_writer.hpp>

#include <core/arch/x86_64/ops.hpp>
#include <core/arch/x86_64/gpr_tags.hpp>
#include <core/compile/compiler.hpp>

#define CodeWriter x86_64::CodeWriter

void CodeWriter::write_return() {
  Ret::write(&$output);
}

void CodeWriter::write_swap(Register a, Register b) {
  Xchg::write(&$output, a, b);
}

void CodeWriter::write_neg(Register r) {
  Neg::write(&$output, r);
}

void CodeWriter::write_assign(Register dst, Register src) {
  Mov::write(&$output, dst, src);
}

void CodeWriter::write_assign(Register dst, i32 src) {
  Mov::write(&$output, dst, src);
}

void CodeWriter::write_assign(Register dst, i64 src) {
  Mov::write(&$output, dst, src);
}

void CodeWriter::write_add(Register dst, i32 src) {
  Add::write(&$output, dst, src);
}

void CodeWriter::write_add(Register dst, i8 src) {
  Add::write(&$output, dst, src);
}

void CodeWriter::write_sub(Register dst, i8 src) {
  Sub::write(&$output, dst, src);
}

void CodeWriter::write_mul(Register dst, i8 src) {
  Imul::write(&$output, dst, Register{2}, src);
}

void CodeWriter::write_div(Register dst, Register src) {
  Mov::write(&$output, rax, dst);
  Cqo::write(&$output);
  Idiv::write(&$output, src);
  Mov::write(&$output, dst, rax);
}

void CodeWriter::write_mod(Register dst, Register src) {
  // Like div, but uses `rdx' idiv result, instead of `rax'
  Mov::write(&$output, rax, dst);
  Cqo::write(&$output);
  Idiv::write(&$output, src);
  Mov::write(&$output, dst, rdx);
}

void CodeWriter::write_bit_and(Register dst, Register src) {
  And::write(&$output, dst, src);
}

void CodeWriter::write_bit_or(Register dst, Register src) {
  Or::write(&$output, dst, src);
}

void CodeWriter::write_while_neq(Register a, i8 b) {
  auto jmp_block = $output.preserve(Jmp::size(i32{}));
  int body_size = write_block();
  Jmp::write(jmp_block, body_size);

  Cmp::write(&$output, a, b);
  Jne::write(&$output, -(body_size + Jne::size(i32{}) + Cmp::size(a, b)));
}

void CodeWriter::write_if_eq(Register a, i8 b) {
  Cmp::write(&$output, a, b);

  auto jne_block = $output.preserve(Jne::size(i32{}));
  int on_true_size = write_block();
  Jne::write(jne_block, on_true_size);
}

void CodeWriter::write_if_else_eq(Register a, i8 b) {
  Cmp::write(&$output, a, b);

  auto jne_block = $output.preserve(Jne::size(i32{}));
  int on_true_size = write_block();
  Jne::write(jne_block, on_true_size + Jmp::size(i32{}));

  auto jmp_block = $output.preserve(Jmp::size(i32{}));
  int on_false_size = write_block();
  Jmp::write(jmp_block, on_false_size);
}
