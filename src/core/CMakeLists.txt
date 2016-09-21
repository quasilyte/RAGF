project(ragf_core)

set(
  ragf_core_src
  io/token_stream.cpp
  io/code_buf.cpp
  codegen/code_writer.cpp
  compile/compile.cpp
  compile/resource_manager.cpp
  arch/x86_64/code_writer.cpp
)

add_library(ragf_core STATIC ${ragf_core_src})
