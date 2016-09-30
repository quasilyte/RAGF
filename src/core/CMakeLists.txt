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
  arch/x86_64/ops.cpp
)

add_library(ragf_core STATIC ${ragf_core_src})
