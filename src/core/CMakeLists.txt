project(ragf_core)

set(
  ragf_core_src
  io/token_stream.cpp
  io/code_buf.cpp
  io/code_buf_slice.cpp
  codegen/code_writer.cpp
  codegen/numerics.cpp
  compile/compiler.cpp
  compile/compile.cpp
  arch/x86_64/code_writer.cpp
  arch/x86_64/ops/add.cpp
  arch/x86_64/ops/sub.cpp
  arch/x86_64/ops/mov.cpp
  arch/x86_64/ops/cmp.cpp
  arch/x86_64/ops/mul_ops.cpp
  arch/x86_64/ops/div_ops.cpp
  arch/x86_64/ops/stack_ops.cpp
  arch/x86_64/ops/shift_ops.cpp
  arch/x86_64/ops/jmp_ops.cpp
  arch/x86_64/ops/bitwise_ops.cpp
  arch/x86_64/ops/fn_ops.cpp
  arch/x86_64/ops/misc_ops.cpp
  arch/x86_64/ops/lea.cpp
)

add_library(ragf_core STATIC ${ragf_core_src})
