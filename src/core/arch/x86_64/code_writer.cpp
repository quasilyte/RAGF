#include <core/arch/x86_64/code_writer.hpp>

#include <core/arch/x86_64/ops.hpp>
#include <core/arch/x86_64/gpr_tags.hpp>
#include <core/compile/compiler.hpp>

#define CodeWriter x86_64::CodeWriter

void CodeWriter::write_return() {
  Ret::write(&$output);
}

void CodeWriter::write_return(Reg r) {
  Mov::write(&$output, rax, r);
  Ret::write(&$output);
}

void CodeWriter::write_push(const Reg* regs, int count) {
  auto q = regs + count;
  while (regs < q) {
    Push::write(&$output, *regs++);
  }
}

void CodeWriter::write_pop(const Reg* regs, int count) {
  auto q = regs + count;
  while (regs < q) {
    Pop::write(&$output, *--q);
  }
}

void CodeWriter::write_swap(Reg a, Reg b) {
  Xchg::write(&$output, a, b);
}

void CodeWriter::write_neg(Reg r) {
  Neg::write(&$output, r);
}

void CodeWriter::write_assign(Reg dst, Reg src) {
  Mov::write(&$output, dst, src);
}

void CodeWriter::write_assign(Reg dst, i32 src) {
  if (src == 0) Xor::write(&$output, dst, dst);
  else          Mov::write(&$output, dst, src);
}

void CodeWriter::write_assign(Reg dst, i64 src) {
  if (src == 0) Xor::write(&$output, dst, dst);
  else          Mov::write(&$output, dst, src);
}

void CodeWriter::write_assign(Reg dst, Mem64 src, i8 disp) {
  Mov::write(&$output, dst, src, disp);
}

void CodeWriter::write_assign(Reg dst, DataReg) {
  Mov::write(&$output, dst, rdi);
}

void CodeWriter::write_add(Reg dst, i32 src) {
  Add::write(&$output, dst, src);
}

void CodeWriter::write_add(Reg dst, i8 src) {
  Add::write(&$output, dst, src);
}

void CodeWriter::write_add(Reg dst, Reg src) {
  Add::write(&$output, dst, src);
}

void CodeWriter::write_add(Reg dst, Mem64 src) {
  Add::write(&$output, dst, src);
}

void CodeWriter::write_sub(Reg dst, i8 src) {
  Sub::write(&$output, dst, src);
}

void CodeWriter::write_sub(Reg dst, i32 src) {
  Sub::write(&$output, dst, src);
}

void CodeWriter::write_sub(Reg dst, Reg src) {
  Sub::write(&$output, dst, src);
}

void CodeWriter::write_sub(Reg dst, Mem64 src) {
  Sub::write(&$output, dst, src);
}

void CodeWriter::write_mul(IntReg dst, i8 src) {
  Imul::write(&$output, dst, dst, src);
}

void CodeWriter::write_mul(IntReg dst, IntReg src) {
  Imul::write(&$output, dst, src);
}

void CodeWriter::write_div(IntReg dst, IntReg src) {
  Mov::write(&$output, rax, Reg{dst});
  Cqo::write(&$output);
  Idiv::write(&$output, src);
  Mov::write(&$output, Reg{dst}, rax);
}

void CodeWriter::write_mod(IntReg dst, IntReg src) {
  // Like div, but uses `rdx' idiv result, instead of `rax'
  Mov::write(&$output, rax, Reg{dst});
  Cqo::write(&$output);
  Idiv::write(&$output, src);
  Mov::write(&$output, Reg{dst}, rdx);
}

void CodeWriter::write_bit_and(Reg dst, Reg src) {
  And::write(&$output, dst, src);
}

void CodeWriter::write_bit_or(Reg dst, Reg src) {
  Or::write(&$output, dst, src);
}

void CodeWriter::write_shift_left(UintReg r, u8 count) {
  Shl::write(&$output, Reg{r}, count);
}

void CodeWriter::write_shift_left(IntReg r, u8 count) {
  // Because `Sal` & `Shl` are the same
  write_shift_left(UintReg{r}, count);
}

void CodeWriter::write_shift_right(UintReg r, u8 count) {
  Shr::write(&$output, r, count);
}

void CodeWriter::write_shift_right(IntReg r, u8 count) {
  Sar::write(&$output, r, count);
}

void CodeWriter::write_while_neq(Reg a, i8 b) {
  auto jmp_block = $output.preserve(Jmp::size(i32{}));
  int body_size = write_block();
  Jmp::write(jmp_block, body_size);

  Cmp::write(&$output, a, b);
  Jne::write(&$output, -(body_size + Jne::size(i32{}) + Cmp::size(a, b)));
}

void CodeWriter::write_if_eq(Reg a, i8 b) {
  Cmp::write(&$output, a, b);

  auto jne_block = $output.preserve(Jne::size(i32{}));
  int on_true_size = write_block();
  Jne::write(jne_block, on_true_size);
}

void CodeWriter::write_if_else_eq(Reg a, i8 b) {
  Cmp::write(&$output, a, b);

  auto jne_block = $output.preserve(Jne::size(i32{}));
  int on_true_size = write_block();
  Jne::write(jne_block, on_true_size + Jmp::size(i32{}));

  auto jmp_block = $output.preserve(Jmp::size(i32{}));
  int on_false_size = write_block();
  Jmp::write(jmp_block, on_false_size);
}
