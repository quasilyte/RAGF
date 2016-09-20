#include <core/compile/compile.hpp>

#include <core/io/token_stream.hpp>
#include <core/io/code_buf.hpp>
#include <core/codegen/code_writer.hpp>
#include <core/arch/x86_64/code_writer.hpp>

#include <core/compile/helpers.hpp>
#include <core/compile/parsers_macro.hpp>

#include <cstdlib>
#include <cstdio>

class Compiler {
public:
  Compiler(const byte* input, CodeWriter* writer):
  $input{input},
  $writer{writer} {}

  void parse_return() {
    $writer->write_return();
  }

  template<class A, class B>
  void encode(void(CodeWriter::*method)(A, B)) {
    auto a = $input.read<A>();
    auto b = $input.read<B>();
    ($writer->*method)(a, b);
  }

  void parse_assign() {
    switch ($input.read<u16>()) {
    case label(Token::REG, Token::I32):
      return encode<RegIndex, i32>(&CodeWriter::write_assign);
    case label(Token::REG, Token::I64):
      return encode<RegIndex, i64>(&CodeWriter::write_assign);

    default:
      throw "assign: invalid dst/src token";
    }
  }

  void parse_add() {
    switch ($input.read<u16>()) {
    case label(Token::REG, Token::I8):
      return encode<RegIndex, i8>(&CodeWriter::write_add);
    case label(Token::REG, Token::I32):
      return encode<RegIndex, i32>(&CodeWriter::write_add);

    default:
      throw "add: invalid dst/src token";
    }
  }

  void parse_swap() {
    encode<RegIndex, RegIndex>(&CodeWriter::write_swap);
  }

  void parse_neg() {
    $writer->write_neg($input.read<RegIndex>());
  }

  Buf compile();

private:
  TokenStream $input;
  CodeWriter* $writer;
};

Buf Compiler::compile() {
  BEGIN_PARSERS();
    TERMINATING_PARSER(end_of_input);
    PARSER(add);
    PARSER(return);
    PARSER(assign);
    PARSER(swap);
    PARSER(neg);
  END_PARSERS();
}

Buf compile_i86_64(const byte* input) {
  try {
    Compiler compiler{input, new x86_64::CodeWriter{}};
    return compiler.compile();
  } catch (const char* err) {
    fprintf(stderr, "error: %s\n", err);
    exit(1);
  }
}
