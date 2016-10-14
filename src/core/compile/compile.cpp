#include <core/compile/compile.hpp>

#include <core/io/token_stream.hpp>
#include <core/io/code_buf.hpp>
#include <core/codegen/code_writer.hpp>
#include <core/arch/x86_64/code_writer.hpp>

#include <core/compile/compiler.hpp>

#include <cstdlib>

Buf compile_x86_64(const byte* binary_tokens, Buf output) {
  TokenStream tokens{binary_tokens};

  x86_64::CodeWriter writer{output};
  Compiler compiler{tokens};

  writer.set_compiler(&compiler);
  compiler.set_writer(&writer);

  return compiler.compile();
}

Buf compile_x86_64(const byte* binary_tokens) {
  Buf output{static_cast<byte*>(calloc(64, 1)), 64};
  return compile_x86_64(binary_tokens, output);
}
