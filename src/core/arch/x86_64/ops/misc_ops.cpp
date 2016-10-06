#include <core/arch/x86_64/ops/ops.hpp>

#include <core/io/code_buf.hpp>
#include <core/arch/x86_64/encode.hpp>

int Nop::size() { return 1; }
void Nop::write(CodeBuf* output) {
  output->write_byte(0x90);
}

int Cqo::size() { return 2; }
void Cqo::write(CodeBuf* output) {
  output->write_byte(REX_W);
  output->write_byte(0x99);
}
