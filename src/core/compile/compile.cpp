#include <core/compile/compile.hpp>

#include <core/io/token_stream.hpp>
#include <core/io/code_buf.hpp>
#include <core/codegen/code_writer.hpp>
#include <core/arch/x86_64/code_writer.hpp>

#include <core/compile/helpers.hpp>

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

  template<class DST, class SRC>
  void write_assign() {
    auto dst = $input.read<DST>();
    auto src = $input.read<SRC>();
    $writer->write_assign(dst, src);
  }

  template<class DST, class SRC>
  void write_add() {
    auto dst = $input.read<DST>();
    auto src = $input.read<SRC>();
    $writer->write_add(dst, src);
  }

  void parse_assign() {
    switch ($input.read<u16>()) {
    case label(Token::REG, Token::I32):
      return write_assign<RegIndex, i32>();
    case label(Token::REG, Token::I64):
      return write_assign<RegIndex, i64>();

    default:
      throw "assign: invalid dst/src token";
    }
  }

  void parse_add() {
    switch ($input.read<u16>()) {
    case label(Token::REG, Token::I32):
      return write_add<RegIndex, i32>();

    default:
      throw "add: invalid dst/src token";
    }
  }

  Buf compile() {
    for (;;) {
      switch ($input.read_token()) {
      case Token::END_OF_INPUT:
        return $writer->get_buf();

      case Token::ASSIGN:
        parse_assign();
        break;

      case Token::ADD:
        parse_add();
        break;

      case Token::RETURN:
        parse_return();
        break;

      default:
        throw "unexpected top level token";
      }
    }
  }

private:
  TokenStream $input;
  CodeWriter* $writer;
};

Buf compile_i86_64(const byte* input) {
  try {
    Compiler compiler{input, new x86_64::CodeWriter{}};
    return compiler.compile();
  } catch (const char* err) {
    fprintf(stderr, "error: %s\n", err);
    exit(1);
  }
}
